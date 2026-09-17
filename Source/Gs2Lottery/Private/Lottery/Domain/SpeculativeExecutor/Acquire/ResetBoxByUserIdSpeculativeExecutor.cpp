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
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Lottery/Domain/SpeculativeExecutor/Acquire/ResetBoxByUserIdSpeculativeExecutor.h"
#include "Lottery/Domain/Gs2Lottery.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Lottery/Model/Cache/BoxItems.h"

namespace
{
    class FResetBoxSpeculativeCommit final
    {
    public:
        FResetBoxSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString>& NamespaceName,
            const FString& UserId,
            const TOptional<FString>& PrizeTableName,
            const TOptional<int32>& TimeOffset,
            const FString& ExpectedBoxId
        ):
            Cache(Cache),
            NamespaceName(NamespaceName),
            UserId(UserId),
            PrizeTableName(PrizeTableName),
            TimeOffset(TimeOffset),
            ExpectedBoxId(ExpectedBoxId)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(
                NamespaceName, UserId, TimeOffset
            ) + TEXT(":") + Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheKey(
                PrizeTableName
            );
        }

        bool CanPrepare() const
        {
            TSharedPtr<void> Next;
            return TryCompose(nullptr, false, Next);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                Gs2::Lottery::Model::FBoxItemsPtr Source;
                if (HasCurrent)
                {
                    if (!Current.IsValid())
                    {
                        Next = nullptr;
                        return false;
                    }
                    Source = StaticCastSharedPtr<Gs2::Lottery::Model::FBoxItems>(Current);
                }
                else if (!Gs2::Lottery::Model::Cache::FBoxItemsCache::TryGet(
                    Cache, NamespaceName, UserId, PrizeTableName, TimeOffset, &Source
                ))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Reset(Source);
                return Next.IsValid();
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            if (!State.IsValid()) return;
            const auto Item = StaticCastSharedPtr<Gs2::Lottery::Model::FBoxItems>(State);
            if (IsExpected(Item))
            {
                Gs2::Lottery::Model::Cache::FBoxItemsCache::Put(
                    Cache, NamespaceName, UserId, PrizeTableName, TimeOffset, Item
                );
            }
        }

    private:
        bool IsExpected(const Gs2::Lottery::Model::FBoxItemsPtr& Item) const
        {
            return Item.IsValid() &&
                Item->GetBoxId().IsSet() &&
                Item->GetBoxId().Get(FString()) == ExpectedBoxId &&
                Item->GetUserId().IsSet() &&
                Item->GetUserId().Get(FString()) == UserId &&
                Item->GetPrizeTableName().IsSet() &&
                Item->GetPrizeTableName().Get(FString()) == PrizeTableName.Get(FString());
        }

        Gs2::Lottery::Model::FBoxItemsPtr Reset(
            const Gs2::Lottery::Model::FBoxItemsPtr& Source
        ) const
        {
            if (!IsExpected(Source)) return nullptr;
            const auto Items = Source->GetItems();
            if (!Items.IsValid()) return nullptr;

            bool HasInitial = false;
            for (const auto& Item : *Items)
            {
                if (Item.IsValid() && Item->GetInitial().IsSet())
                {
                    HasInitial = true;
                    break;
                }
            }
            if (!HasInitial) return nullptr;

            const auto Changed = MakeShared<Gs2::Lottery::Model::FBoxItems>(*Source);
            const auto ChangedItems = MakeShared<TArray<Gs2::Lottery::Model::FBoxItemPtr>>();
            ChangedItems->Reserve(Items->Num());
            for (const auto& Item : *Items)
            {
                if (!Item.IsValid())
                {
                    ChangedItems->Add(nullptr);
                    continue;
                }
                const auto ChangedItem = MakeShared<Gs2::Lottery::Model::FBoxItem>(*Item);
                const auto AcquireActions = Item->GetAcquireActions();
                if (AcquireActions.IsValid())
                {
                    const auto ChangedActions = MakeShared<TArray<Gs2::Lottery::Model::FAcquireActionPtr>>();
                    ChangedActions->Reserve(AcquireActions->Num());
                    for (const auto& Action : *AcquireActions)
                    {
                        Gs2::Lottery::Model::FAcquireActionPtr ChangedAction = nullptr;
                        if (Action.IsValid())
                        {
                            ChangedAction = MakeShared<Gs2::Lottery::Model::FAcquireAction>(*Action);
                        }
                        ChangedActions->Add(ChangedAction);
                    }
                    ChangedItem->WithAcquireActions(ChangedActions);
                }
                if (Item->GetInitial().IsSet())
                {
                    ChangedItem->WithRemaining(Item->GetInitial());
                }
                else
                {
                    ChangedItem->WithRemaining(Item->GetRemaining());
                }
                ChangedItems->Add(ChangedItem);
            }
            Changed->WithItems(ChangedItems);
            if (!IsExpected(Changed)) return Gs2::Lottery::Model::FBoxItemsPtr(nullptr);
            return Changed;
        }

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const TOptional<FString> PrizeTableName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedBoxId;
    };
}

namespace Gs2::Lottery::Domain::SpeculativeExecutor
{

    FString FResetBoxByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Lottery:ResetBoxByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FResetBoxByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr& Request,
        Gs2::Lottery::Model::FBoxItemsPtr Item
    )
    {
        return nullptr;
    }

    FResetBoxByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FResetBoxByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FResetBoxByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        const auto PreparedRequest = Gs2::Lottery::Request::FResetBoxByUserIdRequest::FromJson(
            Request->ToJson()
        );
        const auto PreparedAccessToken = Gs2::Auth::Model::FAccessToken::FromJson(
            AccessToken->ToJson()
        );
        if (!PreparedRequest.IsValid() || !PreparedAccessToken.IsValid() ||
            !PreparedAccessToken->GetUserId().IsSet() ||
            PreparedAccessToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedRequest->GetNamespaceName().IsSet() ||
            PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPrizeTableName().IsSet() ||
            PreparedRequest->GetPrizeTableName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedAccessToken->GetUserId().Get(FString())) return nullptr;

        const auto Region = Domain->RestSession->RegionName();
        const auto OwnerId = Domain->RestSession->OwnerId();
        if (Region.IsEmpty() || OwnerId.IsEmpty()) return nullptr;
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto PrizeTableName = PreparedRequest->GetPrizeTableName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        const FString ExpectedBoxId = FString::Printf(
            TEXT("grn:gs2:%s:%s:lottery:%s:user:%s:box:items:%s"),
            *Region, *OwnerId, *NamespaceName.Get(FString()), *UserId.Get(FString()),
            *PrizeTableName.Get(FString())
        );
        const auto Commit = MakeShared<FResetBoxSpeculativeCommit>(
            Domain->Cache, NamespaceName, UserId.Get(FString()), PrizeTableName, TimeOffset,
            ExpectedBoxId
        );
        if (!Commit->CanPrepare()) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
            Commit->CompositionKey(),
            [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
            { return Commit->TryCompose(Current, HasCurrent, Next); },
            [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FResetBoxByUserIdSpeculativeExecutor::FCommitTask>> FResetBoxByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr FResetBoxByUserIdSpeculativeExecutor::Rate(
        const Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr FResetBoxByUserIdSpeculativeExecutor::Rate(
        const Gs2::Lottery::Request::FResetBoxByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
