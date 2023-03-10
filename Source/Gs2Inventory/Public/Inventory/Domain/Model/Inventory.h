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

    class GS2INVENTORY_API FInventoryDomain:
        public TSharedFromThis<FInventoryDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<int64> OverflowCount;
        TOptional<FString> NextPageToken;
        TOptional<int64> GetOverflowCount() const
        {
            return OverflowCount;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> InventoryName;
    private:

        FString ParentKey;

    public:

        FInventoryDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> InventoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FInventoryDomain(
            const FInventoryDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FInventory>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FGetInventoryByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FInventoryDomain> Self,
                const Request::FGetInventoryByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventory>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetInventoryByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FAddCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryDomain>,
            public TSharedFromThis<FAddCapacityTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FAddCapacityByUserIdRequestPtr Request;
        public:
            explicit FAddCapacityTask(
                const TSharedPtr<FInventoryDomain> Self,
                const Request::FAddCapacityByUserIdRequestPtr Request
            );

            FAddCapacityTask(
                const FAddCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryDomain>> Result
            ) override;
        };
        friend FAddCapacityTask;

        TSharedPtr<FAsyncTask<FAddCapacityTask>> AddCapacity(
            Request::FAddCapacityByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FSetCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryDomain>,
            public TSharedFromThis<FSetCapacityTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FSetCapacityByUserIdRequestPtr Request;
        public:
            explicit FSetCapacityTask(
                const TSharedPtr<FInventoryDomain> Self,
                const Request::FSetCapacityByUserIdRequestPtr Request
            );

            FSetCapacityTask(
                const FSetCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryDomain>> Result
            ) override;
        };
        friend FSetCapacityTask;

        TSharedPtr<FAsyncTask<FSetCapacityTask>> SetCapacity(
            Request::FSetCapacityByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FDeleteInventoryByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FInventoryDomain> Self,
                const Request::FDeleteInventoryByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteInventoryByUserIdRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeItemSetsByUserIdIteratorPtr ItemSets(
        ) const;

        TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain> ItemSet(
            const FString ItemName,
            const TOptional<FString> ItemSetName = TOptional<FString>()
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> InventoryName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FInventory>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FInventoryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventory>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FInventoryDomain> FInventoryDomainPtr;
}
