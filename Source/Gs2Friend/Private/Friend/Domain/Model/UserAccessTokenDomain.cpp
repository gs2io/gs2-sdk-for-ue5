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

#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Follow.h"
#include "Friend/Domain/Model/FollowAccessToken.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
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
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendRequest::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
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
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain> FUserAccessTokenDomain::PublicProfile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr FUserAccessTokenDomain::BlackListUsers(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain> FUserAccessTokenDomain::BlackList(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowAccessTokenDomain> FUserAccessTokenDomain::Follow(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsIteratorPtr FUserAccessTokenDomain::Friends(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeFriends(
        TFunction<void()> Callback,
        const TOptional<bool> WithProfile
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                "FriendUser"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeFriends(
        Gs2::Core::Domain::CallbackID CallbackID,
        const TOptional<bool> WithProfile
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                "FriendUser"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain> FUserAccessTokenDomain::Friend(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIteratorPtr FUserAccessTokenDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "FriendRequest"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeSendRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "FriendRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain> FUserAccessTokenDomain::SendFriendRequest(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr FUserAccessTokenDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeReceiveRequests(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "FriendRequest"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "FriendRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain> FUserAccessTokenDomain::ReceiveFriendRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

