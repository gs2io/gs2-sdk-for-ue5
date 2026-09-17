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

#include "Dictionary/Domain/SpeculativeExecutor/Verify/VerifyEntryByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Dictionary/Domain/Gs2Dictionary.h"
#include "Dictionary/Model/Cache/Entry.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{
namespace
{
    bool DictionaryVerifyEntryPredicate(
        const Gs2::Dictionary::Model::FEntryPtr& Item,
        const bool Found,
        const FString& ExpectedEntryId,
        const FString& UserId,
        const FString& EntryModelName,
        const FString& VerifyType
    )
    {
        if (!Found) return false;
        if (!Item.IsValid()) return VerifyType == TEXT("havent");
        if (!Item->GetEntryId().IsSet() || Item->GetEntryId().Get(FString()) != ExpectedEntryId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != EntryModelName) return false;
        return VerifyType == TEXT("have");
    }
}

    FString FVerifyEntryByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:VerifyEntryByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        TSharedRef<TArray<Gs2::Dictionary::Model::FEntryPtr>> Items
    )
    {
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "havent")
            {
                if (Items->ContainsByPredicate([Request](Gs2::Dictionary::Model::FEntryPtr V)
                {
                    return V->GetName() == Request->GetEntryModelName();
                }))
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("entry", "dictionary.entry.entry.error.have", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "have")
            {
                if (!Items->ContainsByPredicate([Request](Gs2::Dictionary::Model::FEntryPtr V)
                {
                    return V->GetName() == Request->GetEntryModelName();
                }))
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("entry", "dictionary.entry.entry.error.havent", ""));
                        return Arr;
                    }());
                }
            } else {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("verifyType", "invalid", ""));
                    return Arr;
                }());
            }
        }
        return nullptr;
    }

    FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Dictionary::Request::FVerifyEntryByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            Domain->RestSession->OwnerId().IsEmpty() || !PreparedToken->GetUserId().IsSet() ||
            PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetEntryModelName().IsSet() || PreparedRequest->GetEntryModelName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() ||
            (PreparedRequest->GetVerifyType().Get(FString()) != TEXT("have") &&
                PreparedRequest->GetVerifyType().Get(FString()) != TEXT("havent"))) return nullptr;
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const FString EntryModelName = PreparedRequest->GetEntryModelName().Get(FString());
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedEntryId = FString::Printf(
            TEXT("grn:gs2:%s:%s:dictionary:%s:user:%s:entry:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *EntryModelName);
        Gs2::Dictionary::Model::FEntryPtr Cached;
        const bool Found = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
            Domain->Cache, NamespaceName, UserId, EntryModelName, TimeOffset, &Cached);
        if (!Found) return nullptr;
        if (Cached.IsValid() &&
            (!Cached->GetEntryId().IsSet() || Cached->GetEntryId().Get(FString()) != ExpectedEntryId ||
             !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
             !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != EntryModelName)) return nullptr;
        auto Items = MakeShared<TArray<Gs2::Dictionary::Model::FEntryPtr>>();
        if (Cached.IsValid()) Items->Add(Cached);
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Items); Error.IsValid()) return Error;
        const auto Guard = [
            Cache = Domain->Cache, NamespaceName, UserId, EntryModelName, TimeOffset,
            ExpectedEntryId, VerifyType
        ]()
        {
            Gs2::Dictionary::Model::FEntryPtr Current;
            const bool CurrentFound = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
                Cache, NamespaceName, UserId, EntryModelName, TimeOffset, &Current);
            return DictionaryVerifyEntryPredicate(
                Current, CurrentFound, ExpectedEntryId, UserId, EntryModelName, VerifyType);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEntryByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEntryByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Dictionary::Request::FVerifyEntryByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("have")) Inverse->WithVerifyType(TOptional<FString>(TEXT("havent")));
        else if (*Inverse->GetVerifyType() == TEXT("havent")) Inverse->WithVerifyType(TOptional<FString>(TEXT("have")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr FVerifyEntryByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr FVerifyEntryByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
