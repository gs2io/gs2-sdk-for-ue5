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

#include "Exchange/Domain/SpeculativeExecutor/Transaction/AcquireByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Exchange/Model/Cache/Await.h"
#include "Exchange/Model/Cache/RateModel.h"
#include "Exchange/Model/RateModel.h"
#include "Exchange/Request/DeleteAwaitByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Exchange::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeAcquireSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }

        Gs2::Core::Model::FConsumeActionPtr BuildAcquireDeleteAction(
            const TOptional<FString>& NamespaceName,
            const TOptional<FString>& UserId,
            const TOptional<FString>& AwaitName
        )
        {
            const auto Request = MakeShared<Gs2::Exchange::Request::FDeleteAwaitByUserIdRequest>()
                ->WithNamespaceName(NamespaceName)
                ->WithUserId(UserId)
                ->WithAwaitName(AwaitName);
            return MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(FString("Gs2Exchange:DeleteAwaitByUserId"))
                ->WithRequest(SerializeAcquireSnapshot(Request->ToJson()));
        }
    }

    FString FAcquireByUserIdSpeculativeExecutor::Action() {
        return "Gs2Exchange:AcquireByUserId";
    }

    FAcquireByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FAcquireByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FAcquireByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        if (!Result.IsValid() || !Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            if (Result.IsValid()) *Result = nullptr;
            return nullptr;
        }
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Exchange::Request::FAcquireByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedRequest.IsValid() || !PreparedAccessToken->GetUserId().IsSet() ||
            PreparedAccessToken->GetUserId()->IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto AwaitName = PreparedRequest->GetAwaitName();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::Exchange::Model::FAwaitPtr Item;
        const bool AwaitFound = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
            Domain->Cache, NamespaceName, UserId, AwaitName, TimeOffset, &Item);
        const FString ExpectedAwaitId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:user:%s:await:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()), *AwaitName.Get(FString()));
        if (!AwaitFound || !Item.IsValid() || !Item->GetAwaitId().IsSet() ||
            *Item->GetAwaitId() != ExpectedAwaitId || !Item->GetUserId().IsSet() ||
            *Item->GetUserId() != *UserId || !Item->GetName().IsSet() ||
            *Item->GetName() != *AwaitName.Get(FString()) || !Item->GetRateName().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto RateName = Item->GetRateName();
        Gs2::Exchange::Model::FRateModelPtr RateModel;
        const bool RateFound = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
            Domain->Cache, NamespaceName, RateName, TOptional<int32>(), &RateModel);
        const FString ExpectedRateId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *RateName.Get(FString()));
        if (RateFound && (!RateModel.IsValid() || !RateModel->GetRateModelId().IsSet() ||
            *RateModel->GetRateModelId() != ExpectedRateId || !RateModel->GetName().IsSet() ||
            *RateModel->GetName() != *RateName))
        {
            *Result = nullptr;
            return nullptr;
        }
        int64 AcquirableAt = 0;
        if (RateFound)
        {
            if (!RateModel->GetLockTime().IsSet() || !Item->GetExchangedAt().IsSet() ||
                !Item->GetSkipSeconds().IsSet())
            {
                *Result = nullptr;
                return nullptr;
            }
            AcquirableAt = Item->GetExchangedAt().GetValue() +
                (static_cast<int64>(RateModel->GetLockTime().GetValue()) * 60 -
                 Item->GetSkipSeconds().GetValue()) * 1000;
        }
        else
        {
            if (!Item->GetAcquirableAt().IsSet())
            {
                *Result = nullptr;
                return nullptr;
            }
            AcquirableAt = Item->GetAcquirableAt().GetValue();
        }
        const int64 Now = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
            static_cast<int64>(TimeOffset.Get(0)) * 1000;
        if (AcquirableAt > Now)
        {
            *Result = nullptr;
            return nullptr;
        }

        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        if (RateModel.IsValid() && RateModel->GetAcquireActions().IsValid())
        {
            for (const auto& SourceAction : *RateModel->GetAcquireActions())
            {
                Gs2::Core::Model::FAcquireActionPtr Action;
                if (SourceAction.IsValid())
                {
                    Action = MakeShared<Gs2::Core::Model::FAcquireAction>(*SourceAction);
                }
                Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                    Gs2::Core::Model::FAcquireActionPtr(Action),
                    TOptional<FString>(TEXT("userId")), TOptional<FString>(UserId));
                if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
                {
                    for (const auto& Entry : *Config)
                    {
                        if (Entry.IsValid() && Entry->GetValue().IsSet())
                        {
                            Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                                Gs2::Core::Model::FAcquireActionPtr(Action),
                                TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                        }
                    }
                }
                if (const auto ItemConfig = Item->GetConfig(); ItemConfig.IsValid())
                {
                    for (const auto& Entry : *ItemConfig)
                    {
                        if (!Entry.IsValid()) continue;
                        bool Duplicate = false;
                        if (const auto RequestConfig = PreparedRequest->GetConfig(); RequestConfig.IsValid())
                        {
                            for (const auto& RequestEntry : *RequestConfig)
                            {
                                if (RequestEntry.IsValid() && RequestEntry->GetKey() == Entry->GetKey())
                                {
                                    Duplicate = true;
                                    break;
                                }
                            }
                        }
                        if (!Duplicate && Entry->GetValue().IsSet())
                        {
                            Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                                Gs2::Core::Model::FAcquireActionPtr(Action),
                                TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                        }
                    }
                }
                if (Action.IsValid()) AcquireActions->Add(Action);
            }
        }
        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        ConsumeActions->Add(BuildAcquireDeleteAction(NamespaceName, UserId, AwaitName));
        const int64 Count = Item->GetCount().Get(1);
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            PreparedAccessToken, ConsumeActions, AcquireActions, TBigInt<1024, false>(Count));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const FString AwaitSnapshot = SerializeAcquireSnapshot(Item->ToJson());
        const FString RateSnapshot = RateModel.IsValid() ? SerializeAcquireSnapshot(RateModel->ToJson()) : FString();
        const auto PreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(Commit);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([PreparedCommit]() { PreparedCommit->InvokeLegacy(); }),
            [DomainCopy = Domain, NamespaceName, UserId, AwaitName, TimeOffset, AwaitSnapshot,
             RateName, RateFound, RateSnapshot]()
            {
                Gs2::Exchange::Model::FAwaitPtr LiveAwait;
                const bool LiveAwaitFound = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
                    DomainCopy->Cache, NamespaceName, UserId, AwaitName, TimeOffset, &LiveAwait);
                if (!LiveAwaitFound || !LiveAwait.IsValid() ||
                    SerializeAcquireSnapshot(LiveAwait->ToJson()) != AwaitSnapshot) return false;
                Gs2::Exchange::Model::FRateModelPtr LiveRate;
                const bool LiveRateFound = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
                    DomainCopy->Cache, NamespaceName, RateName, TOptional<int32>(), &LiveRate);
                if (LiveRateFound != RateFound) return false;
                return !RateFound || (LiveRate.IsValid() && SerializeAcquireSnapshot(LiveRate->ToJson()) == RateSnapshot);
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcquireByUserIdSpeculativeExecutor::FCommitTask>> FAcquireByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FAcquireByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
