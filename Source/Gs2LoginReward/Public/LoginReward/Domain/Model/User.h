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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "LoginReward/Domain/Iterator/DescribeNamespacesIterator.h"
#include "LoginReward/Domain/Iterator/DescribeBonusModelMastersIterator.h"
#include "LoginReward/Domain/Iterator/DescribeBonusModelsIterator.h"
#include "LoginReward/Domain/Iterator/DescribeReceiveStatusesIterator.h"
#include "LoginReward/Domain/Iterator/DescribeReceiveStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::LoginReward::Domain
{
    class FGs2LoginRewardDomain;
    typedef TSharedPtr<FGs2LoginRewardDomain> FGs2LoginRewardDomainPtr;
}

namespace Gs2::LoginReward::Domain::Model
{
    class FNamespaceDomain;
    class FBonusModelMasterDomain;
    class FCurrentBonusMasterDomain;
    class FBonusModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FBonusDomain;
    class FBonusAccessTokenDomain;
    class FReceiveStatusDomain;
    class FReceiveStatusAccessTokenDomain;

    class GS2LOGINREWARD_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const LoginReward::Domain::FGs2LoginRewardDomainPtr Service;
        const Gs2::LoginReward::FGs2LoginRewardRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusDomain> Bonus(
        );

        Gs2::LoginReward::Domain::Iterator::FDescribeReceiveStatusesByUserIdIteratorPtr ReceiveStatuses(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveStatuses(
            TFunction<void()> Callback
        );

        void UnsubscribeReceiveStatuses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::LoginReward::Domain::Model::FReceiveStatusDomain> ReceiveStatus(
            const FString BonusModelName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
