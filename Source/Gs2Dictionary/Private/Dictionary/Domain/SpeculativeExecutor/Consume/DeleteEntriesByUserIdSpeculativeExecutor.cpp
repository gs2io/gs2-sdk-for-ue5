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

#include "Dictionary/Domain/SpeculativeExecutor/Consume/DeleteEntriesByUserIdSpeculativeExecutor.h"
#include "Dictionary/Domain/Gs2Dictionary.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Dictionary/Model/Cache/Entry.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{

    namespace
    {
        FString SerializeDeleteEntrySnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FDeleteEntriesByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:DeleteEntriesByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteEntriesByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        Gs2::Dictionary::Model::FEntryPtr Item
    )
    {
        return nullptr;
    }

    FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto PreparedRequest = MakeShared<Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequest>(*Request);
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName()->IsEmpty() ||
            !PreparedRequest->GetEntryModelNames().IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        TArray<TPair<FString, FString>> Entries;
        TSet<FString> Seen;
        for (const auto& EntryModelName : *PreparedRequest->GetEntryModelNames())
        {
            if (Seen.Contains(EntryModelName))
            {
                continue;
            }
            Seen.Add(EntryModelName);
            Gs2::Dictionary::Model::FEntryPtr Item;
            const bool Found = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
                Domain->Cache, NamespaceName, UserId, EntryModelName, TimeOffset, &Item);
            const FString ExpectedId = FString::Printf(
                TEXT("grn:gs2:%s:%s:dictionary:%s:user:%s:entry:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                **NamespaceName, **UserId, *EntryModelName);
            if (Found && Item.IsValid() && Item->GetEntryId().IsSet() &&
                *Item->GetEntryId() == ExpectedId && Item->GetUserId().IsSet() &&
                *Item->GetUserId() == *UserId && Item->GetName().IsSet() &&
                *Item->GetName() == EntryModelName)
            {
                Entries.Add(TPair<FString, FString>(EntryModelName, SerializeDeleteEntrySnapshot(Item->ToJson())));
            }
        }
        if (Entries.IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([DomainCopy = Domain, PreparedRequest,
                                           PreparedAccessToken, Entries = MoveTemp(Entries)]()
        {
            for (const auto& Entry : Entries)
            {
                Gs2::Dictionary::Model::FEntryPtr Current;
                const bool Found = Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(
                    DomainCopy->Cache, PreparedRequest->GetNamespaceName(),
                    PreparedAccessToken->GetUserId(), Entry.Key,
                    PreparedAccessToken->GetTimeOffset(), &Current);
                if (Found && Current.IsValid() &&
                    SerializeDeleteEntrySnapshot(Current->ToJson()) == Entry.Value)
                {
                    Gs2::Dictionary::Model::Cache::FEntryCache::Put(
                        DomainCopy->Cache, PreparedRequest->GetNamespaceName(),
                        PreparedAccessToken->GetUserId(), Entry.Key,
                        PreparedAccessToken->GetTimeOffset(), nullptr);
                }
            }
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask>> FDeleteEntriesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr FDeleteEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr FDeleteEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
