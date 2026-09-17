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

#include "Mission/Domain/SpeculativeExecutor/Acquire/SetCounterByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Mission/Domain/SpeculativeExecutor/CounterMutationSpeculativeCommit.h"
#include "Mission/Model/Cache/Counter.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
using Private::FCounterMutationSpeculativeCommit;

FString FSetCounterByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Mission:SetCounterByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FSetCounterByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Mission::Request::FSetCounterByUserIdRequestPtr&, Gs2::Mission::Model::FCounterPtr
)
{
    return nullptr;
}

FSetCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Mission::Request::FSetCounterByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FSetCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FSetCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Mission::Request::FSetCounterByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Mission::Request::FSetCounterByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
        !Prepared->GetCounterName().IsSet() || Prepared->GetCounterName().Get(FString()).IsEmpty()) return nullptr;

    const auto RequestedValues = MakeShared<TArray<Gs2::Mission::Model::FScopedValuePtr>>();
    if (Prepared->GetValues().IsValid())
    {
        for (const auto& Value : *Prepared->GetValues())
        {
            if (Value.IsValid()) RequestedValues->Add(MakeShared<Gs2::Mission::Model::FScopedValue>(*Value));
        }
    }
    Prepared->WithValues(RequestedValues);
    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto UserId = Token->GetUserId();
    const auto CounterName = Prepared->GetCounterName();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedId = FString::Printf(
        TEXT("grn:gs2:%s:%s:mission:%s:user:%s:counter:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *UserId.Get(FString()), *CounterName.Get(FString())
    );
    Gs2::Mission::Model::FCounterPtr Cached;
    if (!Gs2::Mission::Model::Cache::FCounterCache::TryGet(
        Domain->Cache, NamespaceName, UserId, CounterName, TimeOffset, &Cached
    ) || !Cached.IsValid() || !Cached->GetCounterId().IsSet() || Cached->GetCounterId().Get(FString()) != ExpectedId ||
        !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId.Get(FString()) ||
        !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != CounterName.Get(FString())) return nullptr;

    const int64 CurrentTimeMillis = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
        static_cast<int64>(TimeOffset.Get(0)) * 1000;
    const auto Commit = MakeShared<FCounterMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), CounterName.Get(FString()), TimeOffset, ExpectedId,
        Cached->GetRevision(),
        [RequestedValues, CurrentTimeMillis](const Gs2::Mission::Model::FCounterPtr& Current)
        {
            const auto Changed = FCounterMutationSpeculativeCommit::Clone(Current);
            const auto Values = MakeShared<TArray<Gs2::Mission::Model::FScopedValuePtr>>();
            for (const auto& Requested : *RequestedValues)
            {
                if (!Requested.IsValid()) continue;
                Values->Add(MakeShared<Gs2::Mission::Model::FScopedValue>(*Requested)
                    ->WithScopeType(Requested->GetScopeType().IsSet() && !Requested->GetScopeType().Get(FString()).IsEmpty()
                        ? Requested->GetScopeType() : TOptional<FString>(TEXT("resetTiming")))
                    ->WithValue(Requested->GetValue().IsSet() ? Requested->GetValue() : TOptional<int64>(0))
                    ->WithUpdatedAt(CurrentTimeMillis));
            }
            Changed->WithValues(Values)->WithUpdatedAt(CurrentTimeMillis)->WithRevision(0);
            return Changed;
        }
    );
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FSetCounterByUserIdSpeculativeExecutor::FCommitTask>> FSetCounterByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Mission::Request::FSetCounterByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Mission::Request::FSetCounterByUserIdRequestPtr FSetCounterByUserIdSpeculativeExecutor::Rate(
    const Gs2::Mission::Request::FSetCounterByUserIdRequestPtr& Request, const double)
{ return Request; }

Gs2::Mission::Request::FSetCounterByUserIdRequestPtr FSetCounterByUserIdSpeculativeExecutor::Rate(
    const Gs2::Mission::Request::FSetCounterByUserIdRequestPtr& Request, TBigInt<1024, false>)
{ return Request; }
}
