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

#include "Friend/Domain/SpeculativeExecutor/Acquire/UpdateProfileByUserIdSpeculativeExecutor.h"
#include "Friend/Domain/Gs2Friend.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Friend/Model/Cache/Profile.h"
#include "Friend/Model/Cache/PublicProfile.h"

namespace Gs2::Friend::Domain::SpeculativeExecutor
{

    FString FUpdateProfileByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Friend:UpdateProfileByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FUpdateProfileByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr& Request,
        Gs2::Friend::Model::FProfilePtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FUpdateProfileByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Friend::Domain::FGs2FriendDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FUpdateProfileByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUpdateProfileByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto PreparedRequest = MakeShared<Gs2::Friend::Request::FUpdateProfileByUserIdRequest>(*Request);
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        const auto Region = Domain->RestSession->RegionName();
        const auto OwnerId = Domain->RestSession->OwnerId();
        const FString ExpectedProfileId = FString::Printf(
            TEXT("grn:gs2:%s:%s:friend:%s:user:%s"),
            *Region, *OwnerId, **NamespaceName, **UserId);
        Gs2::Friend::Model::FProfilePtr Item;
        const bool Found = Gs2::Friend::Model::Cache::FProfileCache::TryGet(
            Domain->Cache, NamespaceName, UserId, TimeOffset, &Item);
        if (!Found || !Item.IsValid() || !Item->GetProfileId().IsSet() ||
            *Item->GetProfileId() != ExpectedProfileId || !Item->GetUserId().IsSet() ||
            *Item->GetUserId() != *UserId)
        {
            *Result = nullptr;
            return nullptr;
        }
        const int64 PhysicalTimeMillis = static_cast<int64>(
            FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0);
        const int64 LogicalTimeMillis = PhysicalTimeMillis +
            static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const auto PreparedRevision = Item->GetRevision();

        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([Domain = Domain, PreparedRequest, UserId, TimeOffset,
                                           ExpectedProfileId, PreparedRevision,
                                           LogicalTimeMillis]()
        {
            Gs2::Friend::Model::FProfilePtr Current;
            const bool CurrentFound = Gs2::Friend::Model::Cache::FProfileCache::TryGet(
                Domain->Cache, PreparedRequest->GetNamespaceName(), UserId, TimeOffset, &Current);
            if (!CurrentFound || !Current.IsValid() || !Current->GetProfileId().IsSet() ||
                *Current->GetProfileId() != ExpectedProfileId || !Current->GetUserId().IsSet() ||
                *Current->GetUserId() != *UserId)
            {
                return;
            }
            if (Current->GetRevision().IsSet() && *Current->GetRevision() > 0 &&
                (!PreparedRevision.IsSet() || *Current->GetRevision() != *PreparedRevision))
            {
                return;
            }
            const auto Changed = MakeShared<Gs2::Friend::Model::FProfile>(*Current)
                ->WithPublicProfile(PreparedRequest->GetPublicProfile())
                ->WithFollowerProfile(PreparedRequest->GetFollowerProfile())
                ->WithFriendProfile(PreparedRequest->GetFriendProfile())
                ->WithUpdatedAt(LogicalTimeMillis)
                ->WithRevision(0);
            if (!Changed.IsValid() || !Changed->GetProfileId().IsSet() ||
                *Changed->GetProfileId() != ExpectedProfileId || !Changed->GetUserId().IsSet() ||
                *Changed->GetUserId() != *UserId || !Changed->GetRevision().IsSet() ||
                *Changed->GetRevision() != 0)
            {
                return;
            }
            Gs2::Friend::Model::Cache::FProfileCache::Put(
                Domain->Cache, PreparedRequest->GetNamespaceName(), UserId, TimeOffset, Changed);
            Gs2::Friend::Model::Cache::FPublicProfileCache::Put(
                Domain->Cache, PreparedRequest->GetNamespaceName(), UserId, TimeOffset,
                MakeShared<Gs2::Friend::Model::FPublicProfile>()
                    ->WithUserId(UserId)
                    ->WithPublicProfile(Changed->GetPublicProfile()));
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUpdateProfileByUserIdSpeculativeExecutor::FCommitTask>> FUpdateProfileByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Friend::Domain::FGs2FriendDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr FUpdateProfileByUserIdSpeculativeExecutor::Rate(
        const Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr FUpdateProfileByUserIdSpeculativeExecutor::Rate(
        const Gs2::Friend::Request::FUpdateProfileByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
