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

#include "LoginReward/Domain/SpeculativeExecutor/Acquire/DeleteReceiveStatusByUserIdSpeculativeExecutor.h"
#include "LoginReward/Domain/Gs2LoginReward.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "LoginReward/Model/Cache/ReceiveStatus.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
    FString ReceiveStatusSnapshot(const Gs2::LoginReward::Model::FReceiveStatusPtr& Item)
    {
        FString Value;
        auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
        FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
        return Value;
    }
}

namespace Gs2::LoginReward::Domain::SpeculativeExecutor
{

    FString FDeleteReceiveStatusByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2LoginReward:DeleteReceiveStatusByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteReceiveStatusByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr& Request,
        Gs2::LoginReward::Model::FReceiveStatusPtr Item
    )
    {
        return nullptr;
    }

    FDeleteReceiveStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteReceiveStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteReceiveStatusByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetBonusModelName().IsSet() || Prepared->GetBonusModelName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto BonusModelName = Prepared->GetBonusModelName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:loginReward:%s:user:%s:status:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *BonusModelName.Get(FString()));
        Gs2::LoginReward::Model::FReceiveStatusPtr Expected;
        if (!Gs2::LoginReward::Model::Cache::FReceiveStatusCache::TryGet(Domain->Cache, NamespaceName, UserId, BonusModelName, TimeOffset, &Expected) || !Expected.IsValid() || Expected->GetReceiveStatusId().Get(FString()) != ExpectedId || Expected->GetUserId().Get(FString()) != UserId.Get(FString()) || Expected->GetBonusModelName().Get(FString()) != BonusModelName.Get(FString())) return nullptr;
        const auto Snapshot = ReceiveStatusSnapshot(Expected);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, NamespaceName, BonusModelName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId, Snapshot]()
        {
            Gs2::LoginReward::Model::FReceiveStatusPtr Current;
            if (!Gs2::LoginReward::Model::Cache::FReceiveStatusCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, BonusModelName, TimeOffset, &Current) || !Current.IsValid() || Current->GetReceiveStatusId().Get(FString()) != ExpectedId || (Current->GetRevision().Get(0) > 0 && ReceiveStatusSnapshot(Current) != Snapshot)) return;
            Gs2::LoginReward::Model::Cache::FReceiveStatusCache::Put(DomainCopy->Cache, NamespaceName, UserId, BonusModelName, TimeOffset, nullptr);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteReceiveStatusByUserIdSpeculativeExecutor::FCommitTask>> FDeleteReceiveStatusByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr FDeleteReceiveStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr FDeleteReceiveStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
