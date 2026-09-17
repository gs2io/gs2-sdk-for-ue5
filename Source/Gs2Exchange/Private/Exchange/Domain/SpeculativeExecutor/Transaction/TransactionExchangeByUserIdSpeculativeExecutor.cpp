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

#include "Exchange/Domain/SpeculativeExecutor/Transaction/ExchangeByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Exchange/Model/Cache/RateModel.h"
#include "Exchange/Model/RateModel.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Exchange::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeExchangeSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FExchangeByUserIdSpeculativeExecutor::Action() {
        return "Gs2Exchange:ExchangeByUserId";
    }

    FExchangeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FExchangeByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FExchangeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExchangeByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        if (!Result.IsValid() || !Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            if (Result.IsValid()) *Result = nullptr;
            return nullptr;
        }
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Exchange::Request::FExchangeByUserIdRequest::FromJson(Request->ToJson());
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
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetCount().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto RateName = PreparedRequest->GetRateName();
        Gs2::Exchange::Model::FRateModelPtr RateModel;
        const bool RateFound = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
            Domain->Cache, NamespaceName, RateName, TOptional<int32>(), &RateModel);
        const FString ExpectedRateId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *RateName.Get(FString()));
        if (!RateFound || !RateModel.IsValid() || !RateModel->GetRateModelId().IsSet() ||
            *RateModel->GetRateModelId() != ExpectedRateId || !RateModel->GetName().IsSet() ||
            *RateModel->GetName() != *RateName.Get(FString()) || !RateModel->GetTimingType().IsSet() ||
            (*RateModel->GetTimingType() != TEXT("immediate") &&
             *RateModel->GetTimingType() != TEXT("await")))
        {
            *Result = nullptr;
            return nullptr;
        }

        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        if (const auto Sources = RateModel->GetConsumeActions(); Sources.IsValid())
        {
            for (const auto& SourceAction : *Sources)
            {
                Gs2::Core::Model::FConsumeActionPtr Action;
                if (SourceAction.IsValid()) Action = MakeShared<Gs2::Core::Model::FConsumeAction>(*SourceAction);
                Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                    Gs2::Core::Model::FConsumeActionPtr(Action),
                    TOptional<FString>(TEXT("userId")),
                    TOptional<FString>(PreparedAccessToken->GetUserId()));
                if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
                {
                    for (const auto& Entry : *Config)
                    {
                        if (Entry.IsValid() && Entry->GetValue().IsSet())
                        {
                            Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                                Gs2::Core::Model::FConsumeActionPtr(Action),
                                TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                        }
                    }
                }
                if (Action.IsValid()) ConsumeActions->Add(Action);
            }
        }
        if (*RateModel->GetTimingType() != TEXT("await"))
        {
            if (const auto Sources = RateModel->GetAcquireActions(); Sources.IsValid())
            {
                for (const auto& SourceAction : *Sources)
                {
                    if (!SourceAction.IsValid() || (SourceAction->GetAction().IsSet() &&
                        *SourceAction->GetAction() == FExchangeByUserIdSpeculativeExecutor::Action())) continue;
                    Gs2::Core::Model::FAcquireActionPtr Action =
                        MakeShared<Gs2::Core::Model::FAcquireAction>(*SourceAction);
                    Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                        Gs2::Core::Model::FAcquireActionPtr(Action),
                        TOptional<FString>(TEXT("userId")),
                        TOptional<FString>(PreparedAccessToken->GetUserId()));
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
                    if (Action.IsValid()) AcquireActions->Add(Action);
                }
            }
        }
        if (ConsumeActions->Num() == 0 && AcquireActions->Num() == 0)
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            PreparedAccessToken, ConsumeActions, AcquireActions,
            TBigInt<1024, false>(PreparedRequest->GetCount().GetValue()));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const FString Snapshot = SerializeExchangeSnapshot(RateModel->ToJson());
        const auto PreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(Commit);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([PreparedCommit]() { PreparedCommit->InvokeLegacy(); }),
            [DomainCopy = Domain, NamespaceName, RateName, Snapshot]()
            {
                Gs2::Exchange::Model::FRateModelPtr Live;
                const bool Found = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
                    DomainCopy->Cache, NamespaceName, RateName, TOptional<int32>(), &Live);
                return Found && Live.IsValid() && SerializeExchangeSnapshot(Live->ToJson()) == Snapshot;
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExchangeByUserIdSpeculativeExecutor::FCommitTask>> FExchangeByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FExchangeByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
