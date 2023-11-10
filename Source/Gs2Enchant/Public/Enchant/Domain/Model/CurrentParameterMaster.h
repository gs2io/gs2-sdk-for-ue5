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
#include "Enchant/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesByUserIdIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Enchant::Domain
{
    class FGs2EnchantDomain;
    typedef TSharedPtr<FGs2EnchantDomain> FGs2EnchantDomainPtr;
}

namespace Gs2::Enchant::Domain::Model
{
    class FNamespaceDomain;
    class FBalanceParameterModelDomain;
    class FBalanceParameterModelMasterDomain;
    class FRarityParameterModelDomain;
    class FRarityParameterModelMasterDomain;
    class FCurrentParameterMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FBalanceParameterStatusDomain;
    class FBalanceParameterStatusAccessTokenDomain;
    class FRarityParameterStatusDomain;
    class FRarityParameterStatusAccessTokenDomain;

    class GS2ENCHANT_API FCurrentParameterMasterDomain:
        public TSharedFromThis<FCurrentParameterMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Enchant::Domain::FGs2EnchantDomainPtr Service;
        const Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentParameterMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Enchant::Domain::FGs2EnchantDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentParameterMasterDomain(
            const FCurrentParameterMasterDomain& From
        );

        class GS2ENCHANT_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentParameterMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentParameterMasterDomain>& Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FCurrentParameterMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentParameterMasterDomain> Self;
            const Request::FGetCurrentParameterMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentParameterMasterDomain>& Self,
                const Request::FGetCurrentParameterMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FCurrentParameterMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentParameterMasterRequestPtr Request
        );

        class GS2ENCHANT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentParameterMasterDomain> Self;
            const Request::FUpdateCurrentParameterMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentParameterMasterDomain>& Self,
                const Request::FUpdateCurrentParameterMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentParameterMasterRequestPtr Request
        );

        class GS2ENCHANT_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentParameterMasterDomain> Self;
            const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentParameterMasterDomain>& Self,
                const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2ENCHANT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FCurrentParameterMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentParameterMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentParameterMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FCurrentParameterMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Enchant::Model::FCurrentParameterMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCurrentParameterMasterDomain> FCurrentParameterMasterDomainPtr;
}
