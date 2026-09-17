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

#include "Limit/Domain/SpeculativeExecutor/Consume/CountUpByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
#include "Auth/Model/AccessToken.h"
#include "Limit/Domain/Gs2Limit.h"
#include "Limit/Model/Cache/Counter.h"

namespace Gs2::Limit::Domain::SpeculativeExecutor
{

    FString FCountUpByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Limit:CountUpByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FCountUpByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        Gs2::Limit::Model::FCounterPtr Item
    )
    {
        Item->WithCount(*Item->GetCount() - *Request->GetCountUpValue());
        if (*Item->GetCount() > *Request->GetMaxValue())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FCountUpByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FCountUpByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCountUpByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        const auto Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto Prepared = MakeShared<Gs2::Limit::Request::FCountUpByUserIdRequest>(*Request);
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetLimitName().IsSet() || Prepared->GetLimitName().Get(FString()).IsEmpty() || !Prepared->GetCounterName().IsSet() || Prepared->GetCounterName().Get(FString()).IsEmpty() || !Prepared->GetCountUpValue().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto LimitName = Prepared->GetLimitName();
        const auto CounterName = Prepared->GetCounterName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:limit:%s:user:%s:limit:%s:counter:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *LimitName.Get(FString()), *CounterName.Get(FString()));
        Gs2::Limit::Model::FCounterPtr Item;
        if (!Gs2::Limit::Model::Cache::FCounterCache::TryGet(Domain->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Item) || !Item.IsValid() || Item->GetCounterId().Get(FString()) != ExpectedId || Item->GetUserId().Get(FString()) != UserId.Get(FString()) || Item->GetLimitName().Get(FString()) != LimitName.Get(FString()) || Item->GetName().Get(FString()) != CounterName.Get(FString())) return nullptr;
        const int32 CountUpValue = Prepared->GetCountUpValue().Get(0);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>(
            [DomainCopy = Domain, NamespaceName, LimitName, CounterName, UserId, TimeOffset, ExpectedId, CountUpValue]()
        {
            Gs2::Limit::Model::FCounterPtr Live;
            if (!Gs2::Limit::Model::Cache::FCounterCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Live) || !Live.IsValid() || Live->GetCounterId().Get(FString()) != ExpectedId || Live->GetUserId().Get(FString()) != UserId.Get(FString()) || Live->GetLimitName().Get(FString()) != LimitName.Get(FString()) || Live->GetName().Get(FString()) != CounterName.Get(FString()) || !Live->GetCount().IsSet()) return;
            const int64 ChangedCount = static_cast<int64>(Live->GetCount().Get(0)) + CountUpValue;
            if (ChangedCount < TNumericLimits<int32>::Min() || ChangedCount > TNumericLimits<int32>::Max()) return;
            auto Changed = MakeShared<Gs2::Limit::Model::FCounter>(*Live);
            Changed->WithCount(static_cast<int32>(ChangedCount))->WithRevision(0);
            Gs2::Limit::Model::Cache::FCounterCache::Put(DomainCopy->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCountUpByUserIdSpeculativeExecutor::FCommitTask>> FCountUpByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Limit::Request::FCountUpByUserIdRequestPtr FCountUpByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid())
        {
            return Request;
        }
        int32 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetCountUpValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithCountUpValue(Value);
        return Request;
    }

    Gs2::Limit::Request::FCountUpByUserIdRequestPtr FCountUpByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid())
        {
            return Request;
        }
        int32 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetCountUpValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithCountUpValue(Value);
        return Request;
    }
}
