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

    class GS2LOGINREWARD_API FBonusModelDomain:
        public TSharedFromThis<FBonusModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::LoginReward::FGs2LoginRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> BonusModelName;
    private:

        FString ParentKey;

    public:

        FBonusModelDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> BonusModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBonusModelDomain(
            const FBonusModelDomain& From
        );

        class GS2LOGINREWARD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FBonusModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBonusModelDomain> Self;
            const Request::FGetBonusModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBonusModelDomain> Self,
                const Request::FGetBonusModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBonusModelRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> BonusModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> BonusModelName
        );

        class GS2LOGINREWARD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FBonusModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBonusModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBonusModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::LoginReward::Model::FBonusModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FBonusModelDomain> FBonusModelDomainPtr;
}
