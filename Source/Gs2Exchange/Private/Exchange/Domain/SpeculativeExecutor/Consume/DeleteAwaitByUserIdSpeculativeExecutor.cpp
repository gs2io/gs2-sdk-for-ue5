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

#include "Exchange/Domain/SpeculativeExecutor/Consume/DeleteAwaitByUserIdSpeculativeExecutor.h"
#include "Exchange/Domain/Gs2Exchange.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Exchange/Model/Cache/Await.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Exchange::Domain::SpeculativeExecutor
{

    namespace
    {
        FString SerializeDeleteAwaitSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FDeleteAwaitByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Exchange:DeleteAwaitByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteAwaitByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        Gs2::Exchange::Model::FAwaitPtr Item
    )
    {
        return nullptr;
    }

    FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto PreparedRequest = MakeShared<Gs2::Exchange::Request::FDeleteAwaitByUserIdRequest>(*Request);
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName()->IsEmpty() ||
            !PreparedRequest->GetAwaitName().IsSet() || PreparedRequest->GetAwaitName()->IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto AwaitName = PreparedRequest->GetAwaitName();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:user:%s:await:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            **NamespaceName, **UserId, **AwaitName);
        Gs2::Exchange::Model::FAwaitPtr Item;
        const bool Found = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
            Domain->Cache, NamespaceName, UserId, AwaitName, TimeOffset, &Item);
        if (!Found || !Item.IsValid() || !Item->GetAwaitId().IsSet() ||
            *Item->GetAwaitId() != ExpectedId || !Item->GetUserId().IsSet() ||
            *Item->GetUserId() != *UserId || !Item->GetName().IsSet() ||
            *Item->GetName() != *AwaitName)
        {
            *Result = nullptr;
            return nullptr;
        }
        const FString Snapshot = SerializeDeleteAwaitSnapshot(Item->ToJson());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([DomainCopy = Domain, PreparedRequest,
                                           PreparedAccessToken, Snapshot]()
        {
            Gs2::Exchange::Model::FAwaitPtr Current;
            const bool FoundCurrent = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
                DomainCopy->Cache, PreparedRequest->GetNamespaceName(),
                PreparedAccessToken->GetUserId(), PreparedRequest->GetAwaitName(),
                PreparedAccessToken->GetTimeOffset(), &Current);
            if (!FoundCurrent || !Current.IsValid() ||
                SerializeDeleteAwaitSnapshot(Current->ToJson()) != Snapshot)
            {
                return;
            }
            Gs2::Exchange::Model::Cache::FAwaitCache::Put(
                DomainCopy->Cache, PreparedRequest->GetNamespaceName(),
                PreparedAccessToken->GetUserId(), PreparedRequest->GetAwaitName(),
                PreparedAccessToken->GetTimeOffset(), nullptr);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask>> FDeleteAwaitByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr FDeleteAwaitByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr FDeleteAwaitByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
