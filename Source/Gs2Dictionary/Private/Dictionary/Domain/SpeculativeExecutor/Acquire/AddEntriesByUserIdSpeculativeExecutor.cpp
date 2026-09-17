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

#include "Dictionary/Domain/SpeculativeExecutor/Acquire/AddEntriesByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Dictionary/Domain/Gs2Dictionary.h"
#include "Dictionary/Model/Cache/Entry.h"
#include "Dictionary/Model/Cache/EntryModel.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{

    FString FAddEntriesByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:AddEntriesByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddEntriesByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr& Request,
        TSharedRef<TArray<Gs2::Dictionary::Model::FEntryPtr>> Items
    )
    {
        for (auto EntryModelName : *Request->GetEntryModelNames())
        {
            if (!Items->ContainsByPredicate([EntryModelName](Gs2::Dictionary::Model::FEntryPtr V)
            {
                return V->GetName() == EntryModelName;
            }))
            {
                Items->Add(
                    MakeShared<Gs2::Dictionary::Model::FEntry>()
                        ->WithName(EntryModelName)
                        ->WithUserId(AccessToken->GetUserId())
                );
            }
        }
        return nullptr;
    }

    FAddEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddEntriesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto PreparedRequest = MakeShared<Gs2::Dictionary::Request::FAddEntriesByUserIdRequest>(*Request);
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName()->IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto Region = Domain->RestSession->RegionName();
        const auto OwnerId = Domain->RestSession->OwnerId();
        TArray<TPair<FString, Gs2::Dictionary::Model::FEntryPtr>> Additions;
        TSet<FString> Seen;
        int32 Handled = 0;
        if (!PreparedRequest->GetEntryModelNames().IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        for (const auto& EntryModelName : *PreparedRequest->GetEntryModelNames())
        {
            if (EntryModelName.IsEmpty() || Seen.Contains(EntryModelName))
            {
                continue;
            }
            Seen.Add(EntryModelName);
            Gs2::Dictionary::Model::FEntryModelPtr Model;
            const bool ModelFound = Gs2::Dictionary::Model::Cache::FEntryModelCache::TryGet(
                Domain->Cache, NamespaceName, EntryModelName, TOptional<int32>(), &Model);
            const FString ExpectedModelId = FString::Printf(
                TEXT("grn:gs2:%s:%s:dictionary:%s:model:%s"),
                *Region, *OwnerId, **NamespaceName, *EntryModelName);
            if (!ModelFound || !Model.IsValid() || !Model->GetEntryModelId().IsSet() ||
                *Model->GetEntryModelId() != ExpectedModelId || !Model->GetName().IsSet() ||
                *Model->GetName() != EntryModelName)
            {
                continue;
            }
            Gs2::Dictionary::Model::FEntryPtr Entry;
            const bool EntryFound = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
                Domain->Cache, NamespaceName, UserId, EntryModelName,
                PreparedAccessToken->GetTimeOffset(), &Entry);
            if (!EntryFound)
            {
                continue;
            }
            const FString ExpectedEntryId = FString::Printf(
                TEXT("grn:gs2:%s:%s:dictionary:%s:user:%s:entry:%s"),
                *Region, *OwnerId, **NamespaceName, **UserId, *EntryModelName);
            if (Entry.IsValid() &&
                (!Entry->GetEntryId().IsSet() || *Entry->GetEntryId() != ExpectedEntryId ||
                 !Entry->GetUserId().IsSet() || *Entry->GetUserId() != *UserId ||
                 !Entry->GetName().IsSet() || *Entry->GetName() != EntryModelName))
            {
                continue;
            }
            ++Handled;
            Additions.Add(TPair<FString, Gs2::Dictionary::Model::FEntryPtr>(
                EntryModelName,
                MakeShared<Gs2::Dictionary::Model::FEntry>()
                    ->WithEntryId(ExpectedEntryId)
                    ->WithUserId(UserId)
                    ->WithName(EntryModelName)
                    ->WithAcquiredAt(static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
                                     static_cast<int64>(PreparedAccessToken->GetTimeOffset().Get(0)) * 1000)));
        }
        if (Handled == 0)
        {
            *Result = nullptr;
            return nullptr;
        }

        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([Domain = Domain, Additions = MoveTemp(Additions),
                                           NamespaceName, UserId,
                                           TimeOffset = PreparedAccessToken->GetTimeOffset(), Region, OwnerId]()
        {
            for (const auto& Addition : Additions)
            {
                Gs2::Dictionary::Model::FEntryModelPtr Model;
                Gs2::Dictionary::Model::FEntryPtr Entry;
                const bool ModelFound = Gs2::Dictionary::Model::Cache::FEntryModelCache::TryGet(
                    Domain->Cache, NamespaceName, Addition.Key, TOptional<int32>(), &Model);
                const bool EntryFound = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
                    Domain->Cache, NamespaceName, UserId, Addition.Key, TimeOffset, &Entry);
                const FString ExpectedModelId = FString::Printf(
                    TEXT("grn:gs2:%s:%s:dictionary:%s:model:%s"),
                    *Region, *OwnerId, **NamespaceName, *Addition.Key);
                if (ModelFound && Model.IsValid() && Model->GetEntryModelId().IsSet() &&
                    *Model->GetEntryModelId() == ExpectedModelId && Model->GetName().IsSet() &&
                    *Model->GetName() == Addition.Key && EntryFound && !Entry.IsValid())
                {
                    Gs2::Dictionary::Model::Cache::FEntryCache::Put(
                        Domain->Cache, NamespaceName, UserId, Addition.Key, TimeOffset, Addition.Value);
                }
            }
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddEntriesByUserIdSpeculativeExecutor::FCommitTask>> FAddEntriesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr FAddEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr FAddEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FAddEntriesByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
