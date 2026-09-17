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

#include "Enchant/Domain/SpeculativeExecutor/Verify/VerifyRarityParameterStatusByUserIdSpeculativeExecutor.h"
#include "Enchant/Model/Cache/RarityParameterStatus.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
namespace Gs2::Enchant::Domain::SpeculativeExecutor
{
namespace
{
    bool EnchantVerifyRarityPredicate(
        const Gs2::Enchant::Model::FRarityParameterStatusPtr& Item,
        const FString& ExpectedId,
        const FString& UserId,
        const FString& ParameterName,
        const FString& PropertyId,
        const FString& VerifyType,
        const TOptional<FString>& ParameterValueName,
        const TOptional<int32>& ParameterCount
    )
    {
        if (!Item.IsValid() || !Item->GetRarityParameterStatusId().IsSet() || Item->GetRarityParameterStatusId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetParameterName().IsSet() || Item->GetParameterName().Get(FString()) != ParameterName ||
            !Item->GetPropertyId().IsSet() || Item->GetPropertyId().Get(FString()) != PropertyId ||
            !Item->GetParameterValues().IsValid()) return false;
        if (VerifyType == TEXT("count")) return ParameterCount.IsSet() && Item->GetParameterValues()->Num() == ParameterCount.Get(0);
        if (!ParameterValueName.IsSet()) return false;
        bool Found = false;
        for (const auto& Value : *Item->GetParameterValues())
        {
            if (Value.IsValid() && Value->GetName().IsSet() && Value->GetName().Get(FString()) == ParameterValueName.Get(FString())) { Found = true; break; }
        }
        if (VerifyType == TEXT("have")) return Found;
        if (VerifyType == TEXT("havent")) return !Found;
        return false;
    }
}
    FString FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Enchant:VerifyRarityParameterStatusByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request,
        Gs2::Enchant::Model::FRarityParameterStatusPtr Item
    )
    {
        if (!Item.IsValid() || !Item->GetParameterValues().IsValid()) return nullptr;
        const auto VerifyType = Request->GetVerifyType().Get(FString());
        bool Satisfied = false;
        if (VerifyType == TEXT("count"))
        {
            Satisfied = Request->GetParameterCount().IsSet() &&
                Item->GetParameterValues()->Num() == Request->GetParameterCount().Get(0);
        }
        else
        {
            const auto ParameterValueName = Request->GetParameterValueName().Get(FString());
            const bool Found = Item->GetParameterValues()->ContainsByPredicate(
                [&ParameterValueName](const Gs2::Enchant::Model::FRarityParameterValuePtr& Value)
                {
                    return Value.IsValid() && Value->GetName().IsSet() &&
                        Value->GetName().Get(FString()) == ParameterValueName;
                });
            Satisfied = VerifyType == TEXT("have") ? Found :
                (VerifyType == TEXT("havent") && !Found);
        }
        if (Satisfied) return nullptr;
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
            return Arr;
        }());
    }

    FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPropertyId().IsSet() || PreparedRequest->GetPropertyId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetMultiplyValueSpecifyingQuantity().IsSet()) PreparedRequest->WithMultiplyValueSpecifyingQuantity(false);
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetParameterName().IsSet() || PreparedRequest->GetParameterName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("havent") && VerifyType != TEXT("have") && VerifyType != TEXT("count")) return nullptr;
        if ((VerifyType == TEXT("have") || VerifyType == TEXT("havent")) && (!PreparedRequest->GetParameterValueName().IsSet() || PreparedRequest->GetParameterValueName().Get(FString()).IsEmpty())) return nullptr;
        if (VerifyType == TEXT("count") && !PreparedRequest->GetParameterCount().IsSet()) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const FString ParameterName = PreparedRequest->GetParameterName().Get(FString());
        const FString PropertyId = PreparedRequest->GetPropertyId().Get(FString());
        const TOptional<FString> ParameterValueName = PreparedRequest->GetParameterValueName();
        const TOptional<int32> ParameterCount = PreparedRequest->GetParameterCount();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:enchant:%s:user:%s:rarity:%s:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *ParameterName, *PropertyId);
        Gs2::Enchant::Model::FRarityParameterStatusPtr Cached;
        if (!Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::TryGet(Domain->Cache, NamespaceName, UserId, ParameterName, PropertyId, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetRarityParameterStatusId().IsSet() || Cached->GetRarityParameterStatusId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetParameterName().IsSet() || Cached->GetParameterName().Get(FString()) != ParameterName ||
            !Cached->GetPropertyId().IsSet() || Cached->GetPropertyId().Get(FString()) != PropertyId ||
            !Cached->GetParameterValues().IsValid()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, ParameterName, PropertyId, TimeOffset, ExpectedId, VerifyType, ParameterValueName, ParameterCount]()
        {
            Gs2::Enchant::Model::FRarityParameterStatusPtr Current;
            if (!Gs2::Enchant::Model::Cache::FRarityParameterStatusCache::TryGet(Cache, NamespaceName, UserId, ParameterName, PropertyId, TimeOffset, &Current) || !Current.IsValid()) return false;
            return EnchantVerifyRarityPredicate(Current, ExpectedId, UserId, ParameterName, PropertyId, VerifyType, ParameterValueName, ParameterCount);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::FCommitTask>> FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::FCommitTask>> FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("have")) Inverse->WithVerifyType(TOptional<FString>(TEXT("havent")));
        else if (*Inverse->GetVerifyType() == TEXT("havent")) Inverse->WithVerifyType(TOptional<FString>(TEXT("have")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr FVerifyRarityParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FVerifyRarityParameterStatusByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
