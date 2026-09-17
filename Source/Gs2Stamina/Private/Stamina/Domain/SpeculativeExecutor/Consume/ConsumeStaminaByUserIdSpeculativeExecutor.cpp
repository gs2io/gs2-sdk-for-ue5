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

#include "Stamina/Domain/SpeculativeExecutor/Consume/ConsumeStaminaByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Stamina/Domain/Gs2Stamina.h"
#include "Stamina/Domain/SpeculativeExecutor/StaminaMutationSpeculativeCommit.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{

    FString FConsumeStaminaByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Stamina:ConsumeStaminaByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeStaminaByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr& Request,
        Gs2::Stamina::Model::FStaminaPtr Item
    )
    {
        (void)Domain;
        (void)AccessToken;
        (void)Request;
        (void)Item;
        return nullptr;
    }

    FConsumeStaminaByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FConsumeStaminaByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeStaminaByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        const auto Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto Prepared = MakeShared<Gs2::Stamina::Request::FConsumeStaminaByUserIdRequest>(*Request);
        if (!Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetConsumeValue().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName().Get(FString());
        const auto UserId = Token->GetUserId().Get(FString());
        const auto StaminaName = Prepared->GetStaminaName().Get(FString());
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedStaminaId = FString::Printf(TEXT("grn:gs2:%s:%s:stamina:%s:user:%s:stamina:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *StaminaName);
        Gs2::Stamina::Model::FStaminaPtr Item;
        if (!Gs2::Stamina::Model::Cache::FStaminaCache::TryGet(Domain->Cache, NamespaceName, UserId, StaminaName, TimeOffset, &Item) ||
            !Item.IsValid() || !Item->GetStaminaId().IsSet() || Item->GetStaminaId().Get(FString()) != ExpectedStaminaId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetStaminaName().IsSet() || Item->GetStaminaName().Get(FString()) != StaminaName || !Item->GetValue().IsSet()) return nullptr;
        const int64 ConsumeValue = Prepared->GetConsumeValue().Get(0);
        *Result = FStaminaMutationSpeculativeCommit::Create(
            Domain, NamespaceName, UserId, StaminaName, TimeOffset, ExpectedStaminaId, FString(), Item->GetRevision(), false,
            [ConsumeValue](const Gs2::Stamina::Model::FStaminaPtr& Current, const TOptional<int32>&)
            {
                if (!Current->GetValue().IsSet()) return false;
                const int64 Value = static_cast<int64>(Current->GetValue().Get(0)) - ConsumeValue;
                if (Value < 0) return false;
                Current->WithValue(FStaminaMutationSpeculativeCommit::Clamp(Value, TOptional<int32>()));
                return true;
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FConsumeStaminaByUserIdSpeculativeExecutor::FCommitTask>> FConsumeStaminaByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr FConsumeStaminaByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetConsumeValue().IsSet())
        {
            Request->WithConsumeValue(*Request->GetConsumeValue() * Rate);
        }
        return Request;
    }

    Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr FConsumeStaminaByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FConsumeStaminaByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetConsumeValue().IsSet())
        {
            Rate.Multiply(*Request->GetConsumeValue());
            Request->WithConsumeValue(Rate.ToInt());
        }
        return Request;
    }
}
