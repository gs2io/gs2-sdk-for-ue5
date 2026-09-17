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

#include "Limit/Domain/SpeculativeExecutor/Acquire/DeleteCounterByUserIdSpeculativeExecutor.h"
#include "Limit/Domain/Gs2Limit.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Limit/Model/Cache/Counter.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
    FString CounterSnapshot(const Gs2::Limit::Model::FCounterPtr& Item)
    {
        FString Value;
        auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
        FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
        return Value;
    }
}

namespace Gs2::Limit::Domain::SpeculativeExecutor
{

    FString FDeleteCounterByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Limit:DeleteCounterByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteCounterByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        Gs2::Limit::Model::FCounterPtr Item
    )
    {
        return nullptr;
    }

    FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Limit::Request::FDeleteCounterByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetLimitName().IsSet() || Prepared->GetLimitName().Get(FString()).IsEmpty() || !Prepared->GetCounterName().IsSet() || Prepared->GetCounterName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto LimitName = Prepared->GetLimitName();
        const auto CounterName = Prepared->GetCounterName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:limit:%s:user:%s:limit:%s:counter:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *LimitName.Get(FString()), *CounterName.Get(FString()));
        Gs2::Limit::Model::FCounterPtr Expected;
        const bool Found = Gs2::Limit::Model::Cache::FCounterCache::TryGet(Domain->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Expected);
        if (!Found || (Expected.IsValid() && (Expected->GetCounterId().Get(FString()) != ExpectedId || Expected->GetUserId().Get(FString()) != UserId.Get(FString()) || Expected->GetLimitName().Get(FString()) != LimitName.Get(FString()) || Expected->GetName().Get(FString()) != CounterName.Get(FString())))) return nullptr;
        const auto Snapshot = Expected.IsValid() ? CounterSnapshot(Expected) : FString();
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, NamespaceName, LimitName, CounterName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId, Expected, Snapshot]()
        {
            Gs2::Limit::Model::FCounterPtr Current;
            const bool FoundCurrent = Gs2::Limit::Model::Cache::FCounterCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Current);
            if (!FoundCurrent || (!Expected.IsValid() && Current.IsValid()) || (Expected.IsValid() && (!Current.IsValid() || Current->GetCounterId().Get(FString()) != ExpectedId || Current->GetUserId().Get(FString()) != UserId || Current->GetLimitName().Get(FString()) != LimitName.Get(FString()) || Current->GetName().Get(FString()) != CounterName.Get(FString()) || (Current->GetRevision().Get(0) > 0 && CounterSnapshot(Current) != Snapshot)))) return;
            Gs2::Limit::Model::Cache::FCounterCache::Put(DomainCopy->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, nullptr);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteCounterByUserIdSpeculativeExecutor::FCommitTask>> FDeleteCounterByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr FDeleteCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr FDeleteCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FDeleteCounterByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
