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
#include "Inventory/Gs2Inventory.h"
#include "Inventory/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfByUserIdIterator.h"

namespace Gs2::Inventory::Domain::Model
{
    class FNamespaceDomain;
    class FInventoryModelMasterDomain;
    class FInventoryModelDomain;
    class FItemModelMasterDomain;
    class FItemModelDomain;
    class FCurrentItemModelMasterDomain;
    class FInventoryDomain;
    class FInventoryAccessTokenDomain;
    class FItemSetDomain;
    class FItemSetAccessTokenDomain;
    class FReferenceOfDomain;
    class FReferenceOfAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FItemSetEntry;

    class GS2INVENTORY_API FCurrentItemModelMasterDomain:
        public TSharedFromThis<FCurrentItemModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentItemModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentItemModelMasterDomain(
            const FCurrentItemModelMasterDomain& From
        );

        class GS2INVENTORY_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentItemModelMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentItemModelMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FCurrentItemModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentItemModelMasterDomain> Self;
            const Request::FGetCurrentItemModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentItemModelMasterDomain> Self,
                const Request::FGetCurrentItemModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FCurrentItemModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentItemModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentItemModelMasterDomain> Self;
            const Request::FUpdateCurrentItemModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentItemModelMasterDomain> Self,
                const Request::FUpdateCurrentItemModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentItemModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentItemModelMasterDomain> Self;
            const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentItemModelMasterDomain> Self,
                const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FCurrentItemModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FCurrentItemModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentItemModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentItemModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FCurrentItemModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentItemModelMasterDomain> FCurrentItemModelMasterDomainPtr;
}
