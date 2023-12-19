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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::LoginReward::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusDomain> FUserDomain::Bonus(
    )
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FBonusDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    Gs2::LoginReward::Domain::Iterator::FDescribeReceiveStatusesByUserIdIteratorPtr FUserDomain::ReceiveStatuses(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Iterator::FDescribeReceiveStatusesByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceiveStatuses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ReceiveStatus"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeReceiveStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "ReceiveStatus"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FReceiveStatusDomain> FUserDomain::ReceiveStatus(
        const FString BonusModelName
    )
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FReceiveStatusDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            BonusModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(BonusModelName)
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

