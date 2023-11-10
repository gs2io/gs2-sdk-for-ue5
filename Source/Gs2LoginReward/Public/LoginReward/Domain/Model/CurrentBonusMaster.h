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

    class GS2LOGINREWARD_API FCurrentBonusMasterDomain:
        public TSharedFromThis<FCurrentBonusMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const LoginReward::Domain::FGs2LoginRewardDomainPtr Service;
        const Gs2::LoginReward::FGs2LoginRewardRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentBonusMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentBonusMasterDomain(
            const FCurrentBonusMasterDomain& From
        );

        class GS2LOGINREWARD_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentBonusMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentBonusMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2LOGINREWARD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FCurrentBonusMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentBonusMasterDomain> Self;
            const Request::FGetCurrentBonusMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentBonusMasterDomain>& Self,
                const Request::FGetCurrentBonusMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FCurrentBonusMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentBonusMasterRequestPtr Request
        );

        class GS2LOGINREWARD_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentBonusMasterDomain> Self;
            const Request::FUpdateCurrentBonusMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentBonusMasterDomain>& Self,
                const Request::FUpdateCurrentBonusMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentBonusMasterRequestPtr Request
        );

        class GS2LOGINREWARD_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentBonusMasterDomain> Self;
            const Request::FUpdateCurrentBonusMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentBonusMasterDomain>& Self,
                const Request::FUpdateCurrentBonusMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FCurrentBonusMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentBonusMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2LOGINREWARD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::LoginReward::Model::FCurrentBonusMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentBonusMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentBonusMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FCurrentBonusMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::LoginReward::Model::FCurrentBonusMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentBonusMasterDomain> FCurrentBonusMasterDomainPtr;
}
