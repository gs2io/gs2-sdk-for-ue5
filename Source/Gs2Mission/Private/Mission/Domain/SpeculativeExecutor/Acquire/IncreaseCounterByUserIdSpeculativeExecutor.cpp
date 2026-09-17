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

#include "Mission/Domain/SpeculativeExecutor/Acquire/IncreaseCounterByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Mission/Domain/SpeculativeExecutor/CounterMutationSpeculativeCommit.h"
#include "Mission/Model/Cache/Counter.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
using Private::FCounterMutationSpeculativeCommit;

FString FIncreaseCounterByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Mission:IncreaseCounterByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FIncreaseCounterByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr&, Gs2::Mission::Model::FCounterPtr
)
{
    return nullptr;
}

FIncreaseCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FIncreaseCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FIncreaseCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Mission::Request::FIncreaseCounterByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty() || !Prepared->GetValue().IsSet()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
        !Prepared->GetCounterName().IsSet() || Prepared->GetCounterName().Get(FString()).IsEmpty()) return nullptr;

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
        !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != CounterName.Get(FString()) ||
        !Cached->GetValues().IsValid()) return nullptr;

    const int64 CurrentTimeMillis = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
        static_cast<int64>(TimeOffset.Get(0)) * 1000;
    const int64 RequestedValue = Prepared->GetValue().Get(0);
    const auto Commit = MakeShared<FCounterMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), CounterName.Get(FString()), TimeOffset, ExpectedId,
        Cached->GetRevision(),
        [RequestedValue, CurrentTimeMillis](const Gs2::Mission::Model::FCounterPtr& Current)
        {
            bool ChangedAny = false;
            const auto Changed = FCounterMutationSpeculativeCommit::Clone(Current);
            const auto Values = MakeShared<TArray<Gs2::Mission::Model::FScopedValuePtr>>();
            constexpr int64 PositiveLimit = 9223372036854775805LL;
            for (const auto& Existing : *Current->GetValues())
            {
                if (!Existing.IsValid()) continue;
                const auto Value = MakeShared<Gs2::Mission::Model::FScopedValue>(*Existing);
                Values->Add(Value);
                if (!Value->GetScopeType().IsSet() || Value->GetScopeType().Get(FString()) != TEXT("resetTiming") ||
                    (Value->GetNextResetAt().IsSet() && Value->GetNextResetAt().Get(0) <= CurrentTimeMillis) ||
                    !Value->GetValue().IsSet()) continue;
                ChangedAny = true;
                const int64 Base = Value->GetValue().Get(0);
                int64 Result = Base;
                if (RequestedValue > 0 && Base > PositiveLimit - RequestedValue) Result = PositiveLimit;
                else if (RequestedValue < 0 && Base < TNumericLimits<int64>::Min() - RequestedValue) Result = TNumericLimits<int64>::Min();
                else Result = Base + RequestedValue;
                Value->WithValue(Result)->WithUpdatedAt(CurrentTimeMillis);
            }
            if (!ChangedAny) return Current;
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

TSharedPtr<FAsyncTask<FIncreaseCounterByUserIdSpeculativeExecutor::FCommitTask>> FIncreaseCounterByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr FIncreaseCounterByUserIdSpeculativeExecutor::Rate(
    const Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr& Request, const double Rate)
{
    if (Request->GetValue().IsSet()) Request->WithValue(*Request->GetValue() * Rate);
    return Request;
}

Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr FIncreaseCounterByUserIdSpeculativeExecutor::Rate(
    const Gs2::Mission::Request::FIncreaseCounterByUserIdRequestPtr& Request, TBigInt<1024, false> Rate)
{
    if (Request->GetValue().IsSet()) { Rate.Multiply(*Request->GetValue()); Request->WithValue(Rate.ToInt()); }
    return Request;
}
}
