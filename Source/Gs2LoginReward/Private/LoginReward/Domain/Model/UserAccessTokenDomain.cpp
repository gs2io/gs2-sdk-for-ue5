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

#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/BonusModelMaster.h"
#include "LoginReward/Domain/Model/CurrentBonusMaster.h"
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"
#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::LoginReward::Domain::Model
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
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain> FUserAccessTokenDomain::Bonus(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::LoginReward::Domain::Iterator::FDescribeReceiveStatusesIteratorPtr FUserAccessTokenDomain::ReceiveStatuses(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Iterator::FDescribeReceiveStatusesIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeReceiveStatuses(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ReceiveStatus"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeReceiveStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "ReceiveStatus"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FReceiveStatusAccessTokenDomain> FUserAccessTokenDomain::ReceiveStatus(
        const FString BonusModelName
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FReceiveStatusAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            BonusModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(BonusModelName)
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

