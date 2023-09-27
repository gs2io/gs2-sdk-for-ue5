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

#include "Friend/Domain/Model/Friend.h"
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

    FFriendDomain::FFriendDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile
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
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Friend"
        ))
    {
    }

    FFriendDomain::FFriendDomain(
        const FFriendDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        WithProfile(From.WithProfile),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserDomain> FFriendDomain::FriendUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            WithProfile,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    FString FFriendDomain::CreateCacheParentKey(
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

    FString FFriendDomain::CreateCacheKey(
        TOptional<FString> WithProfile
    )
    {
        return FString("") +
            (WithProfile.IsSet() ? *WithProfile : "null");
    }

    FFriendDomain::FModelTask::FModelTask(
        const TSharedPtr<FFriendDomain> Self
    ): Self(Self)
    {

    }

    FFriendDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriend>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Friend::Model::FFriend> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Friend::Model::FFriend>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheKey(
                Self->WithProfile.IsSet() ? Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False")
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendDomain::FModelTask>> FFriendDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFriendDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFriendDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFriendPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Friend::Model::FFriend::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheKey(
                WithProfile.IsSet() ? WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False")
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFriend>(obj));
            }
        );
    }

    void FFriendDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Friend::Model::FFriend::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheKey(
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

