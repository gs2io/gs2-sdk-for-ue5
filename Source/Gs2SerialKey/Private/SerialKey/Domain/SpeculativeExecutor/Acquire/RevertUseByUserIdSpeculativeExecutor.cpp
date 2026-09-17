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

#include "SerialKey/Domain/SpeculativeExecutor/Acquire/RevertUseByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SerialKey/Domain/SpeculativeExecutor/SerialKeySpeculativeCommit.h"
#include "SerialKey/Model/Cache/CampaignModel.h"
#include "SerialKey/Model/Cache/SerialKey.h"
#include "SerialKey/Model/SerialKey.h"

namespace Gs2::SerialKey::Domain::SpeculativeExecutor
{
    using Private::FSerialKeySpeculativeCommit;

    FString FRevertUseByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2SerialKey:RevertUseByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FRevertUseByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr& Request,
        Gs2::SerialKey::Model::FSerialKeyPtr Item
    )
    {
        return nullptr;
    }

    FRevertUseByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FRevertUseByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRevertUseByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr PreparedRequest;
        if (Request.IsValid())
        {
            PreparedRequest = Gs2::SerialKey::Request::FRevertUseByUserIdRequest::FromJson(Request->ToJson());
        }
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid())
        {
            PreparedAccessToken = Gs2::Auth::Model::FAccessToken::FromJson(AccessToken->ToJson());
        }
        if (PreparedRequest.IsValid() && PreparedRequest->GetUserId().IsSet() &&
            *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            if (PreparedAccessToken.IsValid() && PreparedAccessToken->GetUserId().IsSet())
            {
                PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
            }
            else
            {
                PreparedRequest->WithUserId(TOptional<FString>());
            }
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
            !PreparedRequest.IsValid() || !PreparedAccessToken.IsValid() ||
            !PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() ||
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName()->IsEmpty() ||
            !PreparedRequest->GetCode().IsSet() || PreparedRequest->GetCode()->IsEmpty())
        {
            return nullptr;
        }

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString UserId = *PreparedAccessToken->GetUserId();
        const FString Code = *PreparedRequest->GetCode();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::SerialKey::Model::FCampaignModelPtr Campaign;
        if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
            Domain->Cache, NamespaceName, Code, TOptional<int32>(), &Campaign
        ))
        {
            return nullptr;
        }
        if (Campaign.IsValid())
        {
            const FString ExpectedCampaignId = FString::Printf(
                TEXT("grn:gs2:%s:%s:serialKey:%s:model:campaign:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                *NamespaceName.Get(FString()), *Code
            );
            if (!Campaign->GetCampaignId().IsSet() || *Campaign->GetCampaignId() != ExpectedCampaignId ||
                !Campaign->GetName().IsSet() || *Campaign->GetName() != Code)
            {
                return nullptr;
            }
            *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
                MakeShared<TFunction<void()>>([]() {}),
                [DomainCopy = Domain, NamespaceName, Code]()
                {
                    Gs2::SerialKey::Model::FCampaignModelPtr Current;
                    if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                        DomainCopy->Cache, NamespaceName, Code, TOptional<int32>(), &Current
                    ) || !Current.IsValid()) return false;
                    const FString ExpectedId = FString::Printf(
                        TEXT("grn:gs2:%s:%s:serialKey:%s:model:campaign:%s"),
                        *DomainCopy->RestSession->RegionName(), *DomainCopy->RestSession->OwnerId(),
                        *NamespaceName.Get(FString()), *Code
                    );
                    return Current->GetCampaignId().IsSet() && *Current->GetCampaignId() == ExpectedId &&
                        Current->GetName().IsSet() && *Current->GetName() == Code;
                }
            );
            return nullptr;
        }

        Gs2::SerialKey::Model::FSerialKeyPtr Item;
        const bool Found = Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
            Domain->Cache, NamespaceName, UserId, Code, TimeOffset, &Item
        );
        const FString ExpectedSerialKeyId = FString::Printf(
            TEXT("grn:gs2:%s:%s:serialKey:%s:serialKey:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *Code
        );
        if (!Found || !Item.IsValid() || !Item->GetSerialKeyId().IsSet() ||
            *Item->GetSerialKeyId() != ExpectedSerialKeyId || !Item->GetCode().IsSet() ||
            *Item->GetCode() != Code)
        {
            return nullptr;
        }

        const int64 LogicalTime = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
            static_cast<int64>(TimeOffset.Get(0)) * 1000;
        TSharedPtr<FSerialKeySpeculativeCommit> Commit;
        Commit = MakeShared<FSerialKeySpeculativeCommit>(
            Domain->Cache, NamespaceName, UserId, Code, TimeOffset, ExpectedSerialKeyId,
            [LogicalTime, Code](const Gs2::SerialKey::Model::FSerialKeyPtr& Current)
                -> Gs2::SerialKey::Model::FSerialKeyPtr
            {
                if (!Current.IsValid() || !Current->GetStatus().IsSet() ||
                    *Current->GetStatus() != TEXT("USED") || !Current->GetCode().IsSet() ||
                    *Current->GetCode() != Code)
                {
                    return nullptr;
                }
                Gs2::SerialKey::Model::FSerialKeyPtr Changed;
                Changed = Gs2::SerialKey::Model::FSerialKey::FromJson(Current->ToJson());
                if (!Changed.IsValid()) return nullptr;
                Changed->WithStatus(FString(TEXT("ACTIVE")))->WithUsedUserId(TOptional<FString>())
                    ->WithUsedAt(TOptional<int64>())->WithUpdatedAt(LogicalTime)->WithRevision(0);
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

    TSharedPtr<FAsyncTask<FRevertUseByUserIdSpeculativeExecutor::FCommitTask>> FRevertUseByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr FRevertUseByUserIdSpeculativeExecutor::Rate(
        const Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr FRevertUseByUserIdSpeculativeExecutor::Rate(
        const Gs2::SerialKey::Request::FRevertUseByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
