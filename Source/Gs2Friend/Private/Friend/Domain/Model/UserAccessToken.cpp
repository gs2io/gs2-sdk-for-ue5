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
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/SendFriendRequestAccessToken.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Domain/Model/FriendRequestAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Friend::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserAccessTokenDomain> Self,
        const Request::FSendRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->SendRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "SendFriendRequest"
                );
                const auto Key = Gs2::Friend::Domain::Model::FSendFriendRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTargetUserId()
                );
                Self->Cache->Put<Gs2::Friend::Model::FFriendRequest>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSendRequestTask>> FUserAccessTokenDomain::SendRequest(
        Request::FSendRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain> FUserAccessTokenDomain::Profile(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain> FUserAccessTokenDomain::PublicProfile(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr FUserAccessTokenDomain::BlackLists(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain> FUserAccessTokenDomain::BlackList(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFollowsIteratorPtr FUserAccessTokenDomain::Follows(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomain> FUserAccessTokenDomain::FollowUser(
        const FString TargetUserId,
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            TargetUserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsIteratorPtr FUserAccessTokenDomain::Friends(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain> FUserAccessTokenDomain::Friend(
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIteratorPtr FUserAccessTokenDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain> FUserAccessTokenDomain::SendFriendRequest(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            TargetUserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr FUserAccessTokenDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain> FUserAccessTokenDomain::ReceiveFriendRequest(
        const FString FromUserId
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            FromUserId
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

