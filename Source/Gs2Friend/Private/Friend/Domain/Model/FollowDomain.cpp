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

#include "Friend/Domain/Model/Follow.h"
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

    FFollowDomain::FFollowDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        WithProfile(WithProfile),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Follow"
        ))
    {
    }

    FFollowDomain::FFollowDomain(
        const FFollowDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        WithProfile(From.WithProfile),
        ParentKey(From.ParentKey)
    {

    }

    FFollowDomain::FFollowTask::FFollowTask(
        const TSharedPtr<FFollowDomain>& Self,
        const Request::FFollowByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFollowDomain::FFollowTask::FFollowTask(
        const FFollowTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FFollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->FollowByUserId(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile == true ? "True" : "False" : "False")
                );
                const auto Key = Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFollowUser::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FFollowUserDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            false,
            Request->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowDomain::FFollowTask>> FFollowDomain::Follow(
        Request::FFollowByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFollowTask>>(this->AsShared(), Request);
    }

    Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIteratorPtr FFollowDomain::Follows(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            WithProfile,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FFollowDomain::SubscribeFollows(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                FString("FollowUser:") + (WithProfile.IsSet() ? *WithProfile == true ? "True" : "False" : "False")
            ),
            Callback
        );
    }

    void FFollowDomain::UnsubscribeFollows(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                FString("FollowUser:") + (WithProfile.IsSet() ? *WithProfile == true ? "True" : "False" : "False")
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserDomain> FFollowDomain::FollowUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    FString FFollowDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> WithProfile,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (WithProfile.IsSet() ? *WithProfile : "null") + ":" +
            ChildType;
    }

    FString FFollowDomain::CreateCacheKey(
        TOptional<FString> WithProfile
    )
    {
        return FString("") +
            (WithProfile.IsSet() ? *WithProfile : "null");
    }

    FFollowDomain::FModelTask::FModelTask(
        const TSharedPtr<FFollowDomain> Self
    ): Self(Self)
    {

    }

    FFollowDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFollow>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Friend::Model::FFollow> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Friend::Model::FFollow>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheKey(
                Self->WithProfile.IsSet() ? Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False")
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowDomain::FModelTask>> FFollowDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFollowDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFollowDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFollowPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FFollow::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheKey(
                WithProfile.IsSet() ? WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False")
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFollow>(obj));
            }
        );
    }

    void FFollowDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FFollow::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheKey(
                WithProfile.IsSet() ? WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False")
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

