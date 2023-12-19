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

#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FFriendUserAccessTokenDomain::FFriendUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<bool> WithProfile,
        const TOptional<FString> TargetUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        WithProfile(WithProfile),
        TargetUserId(TargetUserId),
        ParentKey(Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
            "FriendUser"
        ))
    {
    }

    FFriendUserAccessTokenDomain::FFriendUserAccessTokenDomain(
        const FFriendUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        WithProfile(From.WithProfile),
        TargetUserId(From.TargetUserId),
        ParentKey(From.ParentKey)
    {

    }

    FFriendUserAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FFriendUserAccessTokenDomain>& Self,
        const Request::FGetFriendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithWithProfile(Self->WithProfile)
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->GetFriend(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendUser::TypeName,
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

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FGetTask>> FFriendUserAccessTokenDomain::Get(
        Request::FGetFriendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFriendUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFriendUserAccessTokenDomain>& Self,
        const Request::FDeleteFriendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->DeleteFriend(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Friend::Model::FFriendUser::TypeName, ParentKey, Key);
            }
            {
                const auto ParentKey = Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Friend::Model::FFriendUser::TypeName, ParentKey, Key);
            }
            Self->Gs2->Cache->Delete(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    FString("False"),
                    "FriendUser"
                ),
                Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->UserId()
                )
            );
            Self->Gs2->Cache->Delete(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    FString("True"),
                    "FriendUser"
                ),
                Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->UserId()
                )
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FDeleteTask>> FFriendUserAccessTokenDomain::Delete(
        Request::FDeleteFriendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFriendUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> WithProfile,
        TOptional<FString> TargetUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (WithProfile.IsSet() ? *WithProfile : "null") + ":" +
            (TargetUserId.IsSet() ? *TargetUserId : "null") + ":" +
            ChildType;
    }

    FString FFriendUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TargetUserId
    )
    {
        return FString("") +
            (TargetUserId.IsSet() ? *TargetUserId : "null");
    }

    FFriendUserAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FFriendUserAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FFriendUserAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Friend::Model::FFriendUser> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Friend::Model::FFriendUser>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                Self->TargetUserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Friend::Request::FGetFriendRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->TargetUserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendUser::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "friendUser")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Friend::Model::FFriendUser>(
                Self->ParentKey,
                Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->TargetUserId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FModelTask>> FFriendUserAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFriendUserAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFriendUserAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFriendUserPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                TargetUserId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFriendUser>(obj));
            }
        );
    }

    void FFriendUserAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                TargetUserId
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

