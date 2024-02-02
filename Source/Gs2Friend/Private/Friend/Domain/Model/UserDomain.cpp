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
#include "Friend/Domain/Model/FriendRequest.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserDomain>& Self,
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
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendRequest::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
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
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileDomain> FUserDomain::PublicProfile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIteratorPtr FUserDomain::BlackLists(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListDomain> FUserDomain::BlackList(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowDomain> FUserDomain::Follow(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIteratorPtr FUserDomain::Friends(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendDomain> FUserDomain::Friend(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIteratorPtr FUserDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "FriendRequest"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSendRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "FriendRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain> FUserDomain::SendFriendRequest(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIteratorPtr FUserDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceiveRequests(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "FriendRequest"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "FriendRequest"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain> FUserDomain::ReceiveFriendRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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

