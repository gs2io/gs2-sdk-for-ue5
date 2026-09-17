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

#include "Idle/Domain/SpeculativeExecutor/Acquire/IncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Idle/Domain/SpeculativeExecutor/MaximumIdleMinutesSpeculativeCommit.h"
#include "Idle/Model/Cache/Status.h"
#include "Core/Util/ServerRate.h"

namespace Gs2::Idle::Domain::SpeculativeExecutor
{
using Private::FMaximumIdleMinutesSpeculativeCommit;
FString FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Action() { return FString("Gs2Idle:IncreaseMaximumIdleMinutesByUserId"); }
Gs2::Core::Model::FGs2ErrorPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr&, Gs2::Idle::Model::FStatusPtr
) { return nullptr; }
FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}
Gs2::Core::Model::FGs2ErrorPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
        !Prepared->GetCategoryName().IsSet() || Prepared->GetCategoryName().Get(FString()).IsEmpty()) return nullptr;
    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto CategoryName = Prepared->GetCategoryName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    const int64 LogicalTime = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
        static_cast<int64>(TimeOffset.Get(0)) * 1000;
    const FString ExpectedId = FString::Printf(
        TEXT("grn:gs2:%s:%s:idle:%s:user:%s:categoryModel:%s"), *Domain->RestSession->RegionName(),
        *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *CategoryName.Get(FString())
    );
    Gs2::Idle::Model::FStatusPtr Status;
    if (!Gs2::Idle::Model::Cache::FStatusCache::TryGet(
        Domain->Cache, NamespaceName, UserId, CategoryName, TimeOffset, &Status
    ) || !Status.IsValid() || !Status->GetStatusId().IsSet() || Status->GetStatusId().Get(FString()) != ExpectedId ||
        !Status->GetUserId().IsSet() || Status->GetUserId().Get(FString()) != UserId.Get(FString()) ||
        !Status->GetCategoryName().IsSet() || Status->GetCategoryName().Get(FString()) != CategoryName.Get(FString())) return nullptr;
    const int32 RequestedValue = Prepared->GetIncreaseMinutes().IsSet() ? Prepared->GetIncreaseMinutes().Get(0) : 1;
    const auto Commit = MakeShared<FMaximumIdleMinutesSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), CategoryName.Get(FString()), TimeOffset, ExpectedId,
        [RequestedValue, LogicalTime](const Gs2::Idle::Model::FStatusPtr& Current) -> Gs2::Idle::Model::FStatusPtr
        {
            if (!Current.IsValid() || !Current->GetMaximumIdleMinutes().IsSet()) return Gs2::Idle::Model::FStatusPtr(nullptr);
            const int64 Value = static_cast<int64>(Current->GetMaximumIdleMinutes().Get(0)) + static_cast<int64>(RequestedValue);
            if (Value > 2147483647 || Value < -2147483648) return Gs2::Idle::Model::FStatusPtr(nullptr);
            Gs2::Idle::Model::FStatusPtr Changed = MakeShared<Gs2::Idle::Model::FStatus>(*Current);
            return Changed->WithMaximumIdleMinutes(static_cast<int32>(Value))->WithUpdatedAt(LogicalTime)->WithRevision(0);
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
TSharedPtr<FAsyncTask<FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask>> FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request
) { return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
    const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request,
    const double Rate
)
{
    if (!Request.IsValid()) return Request;
    int64 Value = 0;
    if (!Gs2::Core::Util::TryApplyServerRate(static_cast<int64>(Request->GetIncreaseMinutes().Get(1)), Rate, Value) ||
        Value < TNumericLimits<int32>::Min() || Value > TNumericLimits<int32>::Max())
    {
        Request->WithIncreaseMinutes(0);
    }
    else
    {
        Request->WithIncreaseMinutes(static_cast<int32>(Value));
    }
    return Request;
}
Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
    const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request,
    TBigInt<1024, false> Rate
)
{
    if (!Request.IsValid()) return Request;
    int64 Value = 0;
    if (!Gs2::Core::Util::TryApplyServerRate(static_cast<int64>(Request->GetIncreaseMinutes().Get(1)), Rate, Value) ||
        Value < TNumericLimits<int32>::Min() || Value > TNumericLimits<int32>::Max())
    {
        Request->WithIncreaseMinutes(0);
    }
    else
    {
        Request->WithIncreaseMinutes(static_cast<int32>(Value));
    }
    return Request;
}
}
