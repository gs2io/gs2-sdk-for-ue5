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

    class GS2INVENTORY_API FItemModelMasterDomain:
        public TSharedFromThis<FItemModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
    private:

        FString ParentKey;

    public:

        FItemModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FItemModelMasterDomain(
            const FItemModelMasterDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FItemModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FItemModelMasterDomain> Self;
            const Request::FGetItemModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FItemModelMasterDomain> Self,
                const Request::FGetItemModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FItemModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetItemModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FItemModelMasterDomain> Self;
            const Request::FUpdateItemModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FItemModelMasterDomain> Self,
                const Request::FUpdateItemModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateItemModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FItemModelMasterDomain> Self;
            const Request::FDeleteItemModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FItemModelMasterDomain> Self,
                const Request::FDeleteItemModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteItemModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ItemName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FItemModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FItemModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FItemModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FItemModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FItemModelMasterDomain> FItemModelMasterDomainPtr;
}
