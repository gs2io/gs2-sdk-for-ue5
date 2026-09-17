/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Enchant/Domain/SpeculativeExecutor/Acquire/SetBalanceParameterStatusByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Enchant/Domain/Gs2Enchant.h"
#include "Enchant/Model/Cache/BalanceParameterStatus.h"

namespace Gs2::Enchant::Domain::SpeculativeExecutor
{

    class FBalanceParameterStatusSpeculativeCommit final
    {
    public:
        using FStatusPtr = Gs2::Enchant::Model::FBalanceParameterStatusPtr;
        using FTransform = TFunction<FStatusPtr(const FStatusPtr&)>;
        using FRequestPtr = Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr;
        using FValuePtr = Gs2::Enchant::Model::FBalanceParameterValuePtr;

        static bool IsExpected(
            const FStatusPtr& Item,
            const FString& ExpectedStatusId,
            const FString& UserId,
            const FString& ParameterName,
            const FString& PropertyId
        )
        {
            return Item.IsValid() && Item->GetBalanceParameterStatusId().IsSet() &&
                Item->GetBalanceParameterStatusId().Get(FString()) == ExpectedStatusId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetParameterName().IsSet() && Item->GetParameterName().Get(FString()) == ParameterName &&
                Item->GetPropertyId().IsSet() && Item->GetPropertyId().Get(FString()) == PropertyId;
        }

        static FRequestPtr Snapshot(const FRequestPtr& Request)
        {
            if (!Request.IsValid() || !Request->GetParameterValues().IsValid()) return nullptr;
            const auto OriginalValues = Request->GetParameterValues();
            FRequestPtr Copy = MakeShared<Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequest>(*Request);
            if (!Copy.IsValid()) return nullptr;
            TSharedPtr<TArray<FValuePtr>> Values = MakeShared<TArray<FValuePtr>>();
            for (const auto& Value : *OriginalValues)
            {
                if (Value.IsValid())
                {
                    Values->Add(MakeShared<Gs2::Enchant::Model::FBalanceParameterValue>(*Value));
                }
            }
            Copy->WithParameterValues(Values);
            return Copy;
        }

        static FStatusPtr Transform(
            const FStatusPtr& Source,
            const FRequestPtr& Request,
            const int64 CurrentTimeMillis
        )
        {
            if (!Source.IsValid() || !Request.IsValid()) return nullptr;
            const auto RequestValues = Request->GetParameterValues();
            if (!RequestValues.IsValid() || RequestValues->Num() == 0) return nullptr;
            TSharedPtr<TArray<FValuePtr>> Values = MakeShared<TArray<FValuePtr>>();
            for (const auto& Value : *RequestValues)
            {
                if (Value.IsValid())
                {
                    Values->Add(MakeShared<Gs2::Enchant::Model::FBalanceParameterValue>(*Value));
                }
            }
            if (Values->Num() == 0) return nullptr;
            FStatusPtr Changed = MakeShared<Gs2::Enchant::Model::FBalanceParameterStatus>(*Source);
            if (!Changed.IsValid()) return nullptr;
            Changed->WithParameterValues(Values)->WithUpdatedAt(CurrentTimeMillis)->WithRevision(0);
            return Changed;
        }

        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString> NamespaceName,
            const FString& UserId,
            const FString& ParameterName,
            const FString& PropertyId,
            const TOptional<int32> TimeOffset,
            const FString& ExpectedStatusId,
            const FStatusPtr& PreparedItem,
            FTransform Transform
        )
        {
            if (!Cache.IsValid() || !Transform) return nullptr;
            const FString CompositionKey =
                Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheParentKey(
                    NamespaceName, UserId, TimeOffset
                ) + TEXT(":") +
                Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::CreateCacheKey(
                    ParameterName, PropertyId
                );
            return Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                CompositionKey,
                [Cache, NamespaceName, UserId, ParameterName, PropertyId,
                    TimeOffset, ExpectedStatusId, PreparedItem, Transform](
                    const TSharedPtr<void>& Current,
                    const bool HasCurrent,
                    TSharedPtr<void>& Next
                )
                {
                    try
                    {
                        FStatusPtr Source;
                        if (HasCurrent)
                        {
                            if (!Current.IsValid())
                            {
                                Next = nullptr;
                                return false;
                            }
                            Source = StaticCastSharedPtr<Gs2::Enchant::Model::FBalanceParameterStatus>(Current);
                            if (!IsExpected(Source, ExpectedStatusId, UserId, ParameterName, PropertyId))
                            {
                                Next = nullptr;
                                return false;
                            }
                            const auto Changed = Transform(Source);
                            if (!IsExpected(Changed, ExpectedStatusId, UserId, ParameterName, PropertyId))
                            {
                                Next = nullptr;
                                return false;
                            }
                            Next = Changed;
                            return true;
                        }

                        bool Found = Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::TryGet(
                            Cache, NamespaceName, UserId, ParameterName, PropertyId,
                            TimeOffset, &Source);
                        if (!Found)
                        {
                            Next = nullptr;
                            return false;
                        }
                        if (Source.IsValid())
                        {
                            if (!IsExpected(Source, ExpectedStatusId, UserId, ParameterName, PropertyId))
                            {
                                Next = nullptr;
                                return false;
                            }
                            const auto Changed = Transform(Source);
                            if (!IsExpected(Changed, ExpectedStatusId, UserId, ParameterName, PropertyId))
                            {
                                Next = nullptr;
                                return false;
                            }
                            Next = Changed;
                            return true;
                        }
                        if (!IsExpected(PreparedItem, ExpectedStatusId, UserId, ParameterName, PropertyId))
                        {
                            Next = nullptr;
                            return false;
                        }
                        Next = PreparedItem;
                        return true;
                    }
                    catch (...)
                    {
                        Next = nullptr;
                        return false;
                    }
                },
                [Cache, NamespaceName, UserId, ParameterName, PropertyId,
                    TimeOffset, ExpectedStatusId](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid()) return;
                    const auto Item = StaticCastSharedPtr<Gs2::Enchant::Model::FBalanceParameterStatus>(State);
                    if (IsExpected(Item, ExpectedStatusId, UserId, ParameterName, PropertyId))
                    {
                        Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::Put(
                            Cache, NamespaceName, UserId, ParameterName, PropertyId,
                            TimeOffset, Item
                        );
                    }
                }
            );
        }
    };

    FString FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Enchant:SetBalanceParameterStatusByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        Gs2::Enchant::Model::FBalanceParameterStatusPtr Item
    )
    {
        Item->WithParameterValues(Request->GetParameterValues());
        return nullptr;
    }

    FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        auto PreparedRequest = FBalanceParameterStatusSpeculativeCommit::Snapshot(Request);
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (!PreparedRequest->GetPropertyId().IsSet() || PreparedRequest->GetPropertyId().Get(FString()).IsEmpty()) return nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        const FString ResolvedPropertyId = PreparedRequest->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *PreparedToken->GetUserId().Get(FString()));
        PreparedRequest->WithPropertyId(ResolvedPropertyId);
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetParameterName().IsSet() || PreparedRequest->GetParameterName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPropertyId().IsSet() || PreparedRequest->GetPropertyId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetParameterValues().IsValid() ||
            PreparedRequest->GetParameterValues()->Num() == 0) return nullptr;

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const FString ParameterName = PreparedRequest->GetParameterName().Get(FString());
        const FString PropertyId = PreparedRequest->GetPropertyId().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const int64 CurrentTimeMillis = static_cast<int64>(FDateTime::Now().ToUnixTimestampDecimal() * 1000.0) +
            static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const FString ExpectedStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:enchant:%s:user:%s:balance:%s:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId, *ParameterName, *PropertyId
        );
        FBalanceParameterStatusSpeculativeCommit::FStatusPtr Item;
        bool Found = Gs2::Enchant::Model::Cache::FBalanceParameterStatusCache::TryGet(
            Domain->Cache, NamespaceName, UserId, ParameterName, PropertyId,
            TimeOffset, &Item
        );
        if (!Found) return nullptr;
        if (Item.IsValid() && !FBalanceParameterStatusSpeculativeCommit::IsExpected(
            Item, ExpectedStatusId, UserId, ParameterName, PropertyId)) return nullptr;
        Gs2::Enchant::Model::FBalanceParameterStatusPtr Source = Item;
        if (!Source.IsValid())
        {
            TSharedPtr<TArray<Gs2::Enchant::Model::FBalanceParameterValuePtr>> EmptyValues = MakeShared<TArray<Gs2::Enchant::Model::FBalanceParameterValuePtr>>();
            Source = MakeShared<Gs2::Enchant::Model::FBalanceParameterStatus>(
            );
            Source->WithBalanceParameterStatusId(ExpectedStatusId)
                ->WithUserId(UserId)
                ->WithParameterName(ParameterName)
                ->WithPropertyId(PropertyId)
                ->WithParameterValues(EmptyValues)
                ->WithCreatedAt(CurrentTimeMillis)
                ->WithUpdatedAt(CurrentTimeMillis)
                ->WithRevision(0);
        }
        const auto Transform = [PreparedRequest, CurrentTimeMillis](const FBalanceParameterStatusSpeculativeCommit::FStatusPtr& Source) -> FBalanceParameterStatusSpeculativeCommit::FStatusPtr
        {
            return FBalanceParameterStatusSpeculativeCommit::Transform(Source, PreparedRequest, CurrentTimeMillis);
        };
        const auto PreparedItem = Transform(Source);
        *Result = FBalanceParameterStatusSpeculativeCommit::Create(
            Domain->Cache, NamespaceName, UserId, ParameterName, PropertyId,
            TimeOffset, ExpectedStatusId, PreparedItem, Transform
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask>> FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
