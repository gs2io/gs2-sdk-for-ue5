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

    class GS2LOGINREWARD_API FBonusModelMasterDomain:
        public TSharedFromThis<FBonusModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::LoginReward::FGs2LoginRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> BonusModelName;
    private:

        FString ParentKey;

    public:

        FBonusModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> BonusModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBonusModelMasterDomain(
            const FBonusModelMasterDomain& From
        );

        class GS2LOGINREWARD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FBonusModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBonusModelMasterDomain> Self;
            const Request::FGetBonusModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBonusModelMasterDomain> Self,
                const Request::FGetBonusModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBonusModelMasterRequestPtr Request
        );

        class GS2LOGINREWARD_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FBonusModelMasterDomain> Self;
            const Request::FUpdateBonusModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FBonusModelMasterDomain> Self,
                const Request::FUpdateBonusModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateBonusModelMasterRequestPtr Request
        );

        class GS2LOGINREWARD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FBonusModelMasterDomain> Self;
            const Request::FDeleteBonusModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FBonusModelMasterDomain> Self,
                const Request::FDeleteBonusModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteBonusModelMasterRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FBonusModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBonusModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBonusModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::LoginReward::Model::FBonusModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FBonusModelMasterDomain> FBonusModelMasterDomainPtr;
}
