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

#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
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

    FFollowUserAccessTokenDomain::FFollowUserAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> TargetUserId,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TargetUserId(TargetUserId),
        WithProfile(WithProfile),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            FString("FollowUser:") + (WithProfile.IsSet() ? *WithProfile == true ? "True" : "False" : "False")
        ))
    {
    }

    FFollowUserAccessTokenDomain::FFollowUserAccessTokenDomain(
        const FFollowUserAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FFollowUserAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FFollowUserAccessTokenDomain> Self,
        const Request::FGetFollowRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFollowUserAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowUserAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFollowUser>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId)
            ->WithWithProfile(Self->WithProfile);
        const auto Future = Self->Client->GetFollow(
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
                    FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile == true ? "True" : "False" : "False")
                );
                const auto Key = Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Put<Gs2::Friend::Model::FFollowUser>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowUserAccessTokenDomain::FGetTask>> FFollowUserAccessTokenDomain::Get(
        Request::FGetFollowRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFollowUserAccessTokenDomain::FFollowTask::FFollowTask(
        const TSharedPtr<FFollowUserAccessTokenDomain> Self,
        const Request::FFollowRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFollowUserAccessTokenDomain::FFollowTask::FFollowTask(
        const FFollowTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowUserAccessTokenDomain::FFollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->Follow(
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
                    FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile == true ? "True" : "False" : "False")
                );
                const auto Key = Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Put<Gs2::Friend::Model::FFollowUser>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowUserAccessTokenDomain::FFollowTask>> FFollowUserAccessTokenDomain::Follow(
        Request::FFollowRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFollowTask>>(this->AsShared(), Request);
    }

    FFollowUserAccessTokenDomain::FUnfollowTask::FUnfollowTask(
        const TSharedPtr<FFollowUserAccessTokenDomain> Self,
        const Request::FUnfollowRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFollowUserAccessTokenDomain::FUnfollowTask::FUnfollowTask(
        const FUnfollowTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowUserAccessTokenDomain::FUnfollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->Unfollow(
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
                    FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile == true ? "True" : "False" : "False")
                );
                const auto Key = Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Delete<Gs2::Friend::Model::FFollowUser>(ParentKey, Key);
            }
            {
                const auto ParentKey = Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile != true ? "True" : "False" : "False")
                );
                const auto Key = Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Delete<Gs2::Friend::Model::FFollowUser>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowUserAccessTokenDomain::FUnfollowTask>> FFollowUserAccessTokenDomain::Unfollow(
        Request::FUnfollowRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnfollowTask>>(this->AsShared(), Request);
    }

    FString FFollowUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TargetUserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TargetUserId.IsSet() ? *TargetUserId : "null") + ":" +
            ChildType;
    }

    FString FFollowUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TargetUserId
    )
    {
        return FString() +
            (TargetUserId.IsSet() ? *TargetUserId : "null");
    }

    FFollowUserAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FFollowUserAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FFollowUserAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowUserAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFollowUser>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Friend::Model::FFollowUser>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                Self->TargetUserId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Friend::Request::FGetFollowRequest>()
                    ->WithWithProfile(Self->WithProfile)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "followUser")
                    {
                        Self->Cache->Delete<Gs2::Friend::Model::FFollowUser>(
                            Self->ParentKey,
                            Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                                Self->TargetUserId
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Friend::Model::FFollowUser>(
                Self->ParentKey,
                Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    Self->TargetUserId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowUserAccessTokenDomain::FModelTask>> FFollowUserAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFollowUserAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

