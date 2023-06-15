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
#include "Friend/Domain/Model/FriendRequest.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FFriendUserDomain::FFriendUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile,
        const TOptional<FString> TargetUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        WithProfile(WithProfile),
        TargetUserId(TargetUserId),
        ParentKey(Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
            "FriendUser"
        ))
    {
    }

    FFriendUserDomain::FFriendUserDomain(
        const FFriendUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FFriendUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FFriendUserDomain> Self,
        const Request::FGetFriendByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithWithProfile(Self->WithProfile)
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->GetFriendByUserId(
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
                    Self->UserId,
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FFriendUserDomain::FGetTask>> FFriendUserDomain::Get(
        Request::FGetFriendByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFriendUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFriendUserDomain> Self,
        const Request::FDeleteFriendByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithTargetUserId(Self->TargetUserId);
        const auto Future = Self->Client->DeleteFriendByUserId(
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
                    Self->UserId,
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Delete(Gs2::Friend::Model::FFriendUser::TypeName, ParentKey, Key);
            }
            {
                const auto ParentKey = Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                    "FriendUser"
                );
                const auto Key = Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Cache->Delete(Gs2::Friend::Model::FFriendUser::TypeName, ParentKey, Key);
            }
            Self->Cache->Delete(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    FString("False"),
                    "FriendUser"
                ),
                Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->UserId
                )
            );
            Self->Cache->Delete(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    ResultModel->GetItem()->GetUserId(),
                    FString("True"),
                    "FriendUser"
                ),
                Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                    Self->UserId
                )
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendUserDomain::FDeleteTask>> FFriendUserDomain::Delete(
        Request::FDeleteFriendByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFriendUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> WithProfile,
        TOptional<FString> TargetUserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (WithProfile.IsSet() ? *WithProfile : "null") + ":" +
            (TargetUserId.IsSet() ? *TargetUserId : "null") + ":" +
            ChildType;
    }

    FString FFriendUserDomain::CreateCacheKey(
        TOptional<FString> TargetUserId
    )
    {
        return FString() +
            (TargetUserId.IsSet() ? *TargetUserId : "null");
    }

    FFriendUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FFriendUserDomain> Self
    ): Self(Self)
    {

    }

    FFriendUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Friend::Model::FFriendUser> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Friend::Model::FFriendUser>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FFriendUserDomain::CreateCacheKey(
                Self->TargetUserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Friend::Request::FGetFriendByUserIdRequest>()
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
                Self->Cache->Put(
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
            Self->Cache->TryGet<Gs2::Friend::Model::FFriendUser>(
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

    TSharedPtr<FAsyncTask<FFriendUserDomain::FModelTask>> FFriendUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFriendUserDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

