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

#include "SerialKey/Domain/SpeculativeExecutor/Verify/VerifyCodeByUserIdSpeculativeExecutor.h"
#include "SerialKey/Domain/Gs2SerialKey.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SerialKey/Model/Cache/CampaignModel.h"
#include "SerialKey/Model/Cache/SerialKey.h"
#include "SerialKey/Model/SerialKey.h"

namespace Gs2::SerialKey::Domain::SpeculativeExecutor
{
    namespace
    {
        FString FSerialKeyExpectedCampaignId(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& CampaignModelName
        )
        {
            return FString::Printf(
                TEXT("grn:gs2:%s:%s:serialKey:%s:model:campaign:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                *NamespaceName, *CampaignModelName
            );
        }

        FString FSerialKeyExpectedSerialKeyId(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& Code
        )
        {
            return FString::Printf(
                TEXT("grn:gs2:%s:%s:serialKey:%s:serialKey:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                *NamespaceName, *Code
            );
        }

        bool FSerialKeyStatusMatches(
            const Gs2::SerialKey::Model::FSerialKeyPtr& Item,
            const FString& VerifyType
        )
        {
            if (!Item.IsValid() || !Item->GetStatus().IsSet() || Item->GetStatus()->IsEmpty()) return false;
            if (VerifyType == TEXT("active")) return *Item->GetStatus() == TEXT("ACTIVE");
            return *Item->GetStatus() != TEXT("ACTIVE");
        }

        bool FSerialKeyVerifyCampaignAlias(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const TOptional<FString>& NamespaceName,
            const FString& Code,
            const FString& ExpectedCampaignId,
            const TOptional<FString>& CampaignModelName
        )
        {
            Gs2::SerialKey::Model::FCampaignModelPtr Campaign;
            if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                Domain->Cache, NamespaceName, Code, TOptional<int32>(), &Campaign
            ) || !Campaign.IsValid()) return false;
            if (!Campaign->GetCampaignId().IsSet() || *Campaign->GetCampaignId() != ExpectedCampaignId ||
                !Campaign->GetName().IsSet() || *Campaign->GetName() != Code) return false;
            return !CampaignModelName.IsSet() || *CampaignModelName == Code;
        }

        bool FSerialKeyVerifyItem(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const TOptional<FString>& NamespaceName,
            const FString& UserId,
            const FString& Code,
            const TOptional<int32>& TimeOffset,
            const FString& ExpectedSerialKeyId,
            const FString& CampaignModelName,
            const FString& ExpectedCampaignId,
            const FString& VerifyType
        )
        {
            Gs2::SerialKey::Model::FCampaignModelPtr CampaignByCode;
            if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                Domain->Cache, NamespaceName, Code, TOptional<int32>(), &CampaignByCode
            ) || CampaignByCode.IsValid()) return false;

            Gs2::SerialKey::Model::FSerialKeyPtr Item;
            if (!Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
                Domain->Cache, NamespaceName, UserId, Code, TimeOffset, &Item
            ) || !Item.IsValid() || !Item->GetSerialKeyId().IsSet() ||
                *Item->GetSerialKeyId() != ExpectedSerialKeyId || !Item->GetCode().IsSet() ||
                *Item->GetCode() != Code || !Item->GetCampaignModelName().IsSet() ||
                *Item->GetCampaignModelName() != CampaignModelName ||
                !FSerialKeyStatusMatches(Item, VerifyType)) return false;

            Gs2::SerialKey::Model::FCampaignModelPtr Campaign;
            if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                Domain->Cache, NamespaceName, CampaignModelName, TOptional<int32>(), &Campaign
            ) || !Campaign.IsValid() || !Campaign->GetCampaignId().IsSet() ||
                *Campaign->GetCampaignId() != ExpectedCampaignId || !Campaign->GetName().IsSet() ||
                *Campaign->GetName() != CampaignModelName) return false;
            return true;
        }
    }

    FString FVerifyCodeByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2SerialKey:VerifyCodeByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCodeByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request,
        Gs2::SerialKey::Model::FSerialKeyPtr Item
    )
    {
        return nullptr;
    }

    FVerifyCodeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyCodeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCodeByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr PreparedRequest;
        if (Request.IsValid())
        {
            PreparedRequest = Gs2::SerialKey::Request::FVerifyCodeByUserIdRequest::FromJson(Request->ToJson());
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
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetCode().IsSet() || PreparedRequest->GetCode()->IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() ||
            (*PreparedRequest->GetVerifyType() != TEXT("active") &&
             *PreparedRequest->GetVerifyType() != TEXT("inactive")) ||
            (PreparedRequest->GetCampaignModelName().IsSet() &&
             PreparedRequest->GetCampaignModelName()->IsEmpty()) ||
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId())
        {
            return nullptr;
        }

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString UserId = *PreparedRequest->GetUserId();
        const FString Code = *PreparedRequest->GetCode();
        const FString VerifyType = *PreparedRequest->GetVerifyType();
        const auto CampaignModelName = PreparedRequest->GetCampaignModelName();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::SerialKey::Model::FCampaignModelPtr CampaignByCode;
        if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
            Domain->Cache, NamespaceName, Code, TOptional<int32>(), &CampaignByCode
        ))
        {
            return nullptr;
        }

        const FString ExpectedCampaignByCodeId = FSerialKeyExpectedCampaignId(Domain, *NamespaceName, Code);
        if (CampaignByCode.IsValid())
        {
            if (!CampaignByCode->GetCampaignId().IsSet() || *CampaignByCode->GetCampaignId() != ExpectedCampaignByCodeId ||
                !CampaignByCode->GetName().IsSet() || *CampaignByCode->GetName() != Code)
            {
                return nullptr;
            }
            if (CampaignModelName.IsSet() && *CampaignModelName != Code)
            {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("campaignModelName", "invalid", ""));
                    return Details;
                }());
            }
            *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
                MakeShared<TFunction<void()>>([]() {}),
                [DomainCopy = Domain, NamespaceName, Code, ExpectedCampaignByCodeId, CampaignModelName]()
                {
                    return FSerialKeyVerifyCampaignAlias(
                        DomainCopy, NamespaceName, Code, ExpectedCampaignByCodeId, CampaignModelName
                    );
                }
            );
            return nullptr;
        }

        Gs2::SerialKey::Model::FSerialKeyPtr Item;
        const FString ExpectedSerialKeyId = FSerialKeyExpectedSerialKeyId(Domain, *NamespaceName, Code);
        if (!Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
            Domain->Cache, NamespaceName, UserId, Code, TimeOffset, &Item
        ) || !Item.IsValid() || !Item->GetSerialKeyId().IsSet() ||
            *Item->GetSerialKeyId() != ExpectedSerialKeyId || !Item->GetCode().IsSet() ||
            *Item->GetCode() != Code || !Item->GetCampaignModelName().IsSet() ||
            Item->GetCampaignModelName()->IsEmpty() || !Item->GetStatus().IsSet() ||
            Item->GetStatus()->IsEmpty())
        {
            return nullptr;
        }
        if (CampaignModelName.IsSet() && *CampaignModelName != *Item->GetCampaignModelName())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("campaignModelName", "invalid", ""));
                return Details;
            }());
        }
        if (!FSerialKeyStatusMatches(Item, VerifyType))
        {
            const FString ExpectedStatus = VerifyType == TEXT("inactive") ? TEXT("active") : TEXT("inactive");
            return MakeShared<Gs2::Core::Model::FBadRequestError>([ExpectedStatus]
            {
                auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("status", ExpectedStatus, ""));
                return Details;
            }());
        }
        const FString ItemCampaignModelName = *Item->GetCampaignModelName();
        const FString ExpectedItemCampaignId = FSerialKeyExpectedCampaignId(
            Domain, *NamespaceName, ItemCampaignModelName
        );
        Gs2::SerialKey::Model::FCampaignModelPtr ItemCampaign;
        if (!Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
            Domain->Cache, NamespaceName, ItemCampaignModelName, TOptional<int32>(), &ItemCampaign
        ) || !ItemCampaign.IsValid() || !ItemCampaign->GetCampaignId().IsSet() ||
            *ItemCampaign->GetCampaignId() != ExpectedItemCampaignId ||
            !ItemCampaign->GetName().IsSet() || *ItemCampaign->GetName() != ItemCampaignModelName)
        {
            return nullptr;
        }
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}),
            [DomainCopy = Domain, NamespaceName, UserId, Code, TimeOffset, ExpectedSerialKeyId,
             ItemCampaignModelName, ExpectedItemCampaignId, VerifyType]()
            {
                return FSerialKeyVerifyItem(
                    DomainCopy, NamespaceName, UserId, Code, TimeOffset, ExpectedSerialKeyId,
                    ItemCampaignModelName, ExpectedItemCampaignId, VerifyType
                );
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyCodeByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCodeByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyCodeByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCodeByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::SerialKey::Request::FVerifyCodeByUserIdRequest>(*Request);
        if (!Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("active")) Inverse->WithVerifyType(TOptional<FString>(TEXT("inactive")));
        else if (*Inverse->GetVerifyType() == TEXT("inactive")) Inverse->WithVerifyType(TOptional<FString>(TEXT("active")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr FVerifyCodeByUserIdSpeculativeExecutor::Rate(
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr FVerifyCodeByUserIdSpeculativeExecutor::Rate(
        const Gs2::SerialKey::Request::FVerifyCodeByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
