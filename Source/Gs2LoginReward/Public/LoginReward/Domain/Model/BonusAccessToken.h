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
#include "LoginReward/Gs2LoginReward.h"
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

    class GS2LOGINREWARD_API FBonusAccessTokenDomain:
        public TSharedFromThis<FBonusAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const LoginReward::Domain::FGs2LoginRewardDomainPtr Service;
        const Gs2::LoginReward::FGs2LoginRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FBonusAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBonusAccessTokenDomain(
            const FBonusAccessTokenDomain& From
        );

        class GS2LOGINREWARD_API FReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            const TSharedPtr<FBonusAccessTokenDomain> Self;
            const Request::FReceiveRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FReceiveTask(
                const TSharedPtr<FBonusAccessTokenDomain>& Self,
                const Request::FReceiveRequestPtr Request,
                bool SpeculativeExecute
            );

            FReceiveTask(
                const FReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
            Request::FReceiveRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2LOGINREWARD_API FMissedReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>,
            public TSharedFromThis<FMissedReceiveTask>
        {
            const TSharedPtr<FBonusAccessTokenDomain> Self;
            const Request::FMissedReceiveRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FMissedReceiveTask(
                const TSharedPtr<FBonusAccessTokenDomain>& Self,
                const Request::FMissedReceiveRequestPtr Request,
                bool SpeculativeExecute
            );

            FMissedReceiveTask(
                const FMissedReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>> Result
            ) override;
        };
        friend FMissedReceiveTask;

        TSharedPtr<FAsyncTask<FMissedReceiveTask>> MissedReceive(
            Request::FMissedReceiveRequestPtr Request,
            bool SpeculativeExecute = true
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FBonusAccessTokenDomain> FBonusAccessTokenDomainPtr;
}
