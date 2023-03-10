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
#include "Friend/Domain/Model/FriendRequest.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Friend::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FSendRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendRequestByUserId(
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
                    Self->UserId,
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
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendRequestTask>> FUserDomain::SendRequest(
        Request::FSendRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FProfileDomain> FUserDomain::Profile(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileDomain> FUserDomain::PublicProfile(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIteratorPtr FUserDomain::BlackLists(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListDomain> FUserDomain::BlackList(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIteratorPtr FUserDomain::Follows(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserDomain> FUserDomain::FollowUser(
        const FString TargetUserId,
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            TargetUserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIteratorPtr FUserDomain::Friends(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendDomain> FUserDomain::Friend(
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIteratorPtr FUserDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain> FUserDomain::SendFriendRequest(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            TargetUserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIteratorPtr FUserDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain> FUserDomain::ReceiveFriendRequest(
        const FString FromUserId
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            FromUserId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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

