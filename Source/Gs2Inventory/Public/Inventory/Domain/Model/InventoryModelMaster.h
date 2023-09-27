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
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigInventoryModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigInventoryModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemModelMastersIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemModelsIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Domain/Iterator/DescribeInventoriesByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Iterator/DescribeReferenceOfByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsIterator.h"
#include "Inventory/Domain/Iterator/DescribeSimpleItemsByUserIdIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemsIterator.h"
#include "Inventory/Domain/Iterator/DescribeBigItemsByUserIdIterator.h"

namespace Gs2::Inventory::Domain::Model
{
    class FNamespaceDomain;
    class FInventoryModelMasterDomain;
    class FInventoryModelDomain;
    class FItemModelMasterDomain;
    class FItemModelDomain;
    class FSimpleInventoryModelMasterDomain;
    class FSimpleInventoryModelDomain;
    class FSimpleItemModelMasterDomain;
    class FSimpleItemModelDomain;
    class FBigInventoryModelMasterDomain;
    class FBigInventoryModelDomain;
    class FBigItemModelMasterDomain;
    class FBigItemModelDomain;
    class FCurrentItemModelMasterDomain;
    class FInventoryDomain;
    class FInventoryAccessTokenDomain;
    class FItemSetDomain;
    class FItemSetAccessTokenDomain;
    class FReferenceOfDomain;
    class FReferenceOfAccessTokenDomain;
    class FSimpleInventoryDomain;
    class FSimpleInventoryAccessTokenDomain;
    class FSimpleItemDomain;
    class FSimpleItemAccessTokenDomain;
    class FBigInventoryDomain;
    class FBigInventoryAccessTokenDomain;
    class FBigItemDomain;
    class FBigItemAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FItemSetEntry;

    class GS2INVENTORY_API FInventoryModelMasterDomain:
        public TSharedFromThis<FInventoryModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> InventoryName;
    private:

        FString ParentKey;

    public:

        FInventoryModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> InventoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FInventoryModelMasterDomain(
            const FInventoryModelMasterDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FInventoryModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FInventoryModelMasterDomain> Self;
            const Request::FGetInventoryModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FInventoryModelMasterDomain> Self,
                const Request::FGetInventoryModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetInventoryModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FInventoryModelMasterDomain> Self;
            const Request::FUpdateInventoryModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FInventoryModelMasterDomain> Self,
                const Request::FUpdateInventoryModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateInventoryModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FInventoryModelMasterDomain> Self;
            const Request::FDeleteInventoryModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FInventoryModelMasterDomain> Self,
                const Request::FDeleteInventoryModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteInventoryModelMasterRequestPtr Request
        );

        class GS2INVENTORY_API FCreateItemModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>,
            public TSharedFromThis<FCreateItemModelMasterTask>
        {
            const TSharedPtr<FInventoryModelMasterDomain> Self;
            const Request::FCreateItemModelMasterRequestPtr Request;
        public:
            explicit FCreateItemModelMasterTask(
                const TSharedPtr<FInventoryModelMasterDomain> Self,
                const Request::FCreateItemModelMasterRequestPtr Request
            );

            FCreateItemModelMasterTask(
                const FCreateItemModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>> Result
            ) override;
        };
        friend FCreateItemModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateItemModelMasterTask>> CreateItemModelMaster(
            Request::FCreateItemModelMasterRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeItemModelMastersIteratorPtr ItemModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeItemModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeItemModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain> ItemModelMaster(
            const FString ItemName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> InventoryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> InventoryName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FInventoryModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FInventoryModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FInventoryModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FInventoryModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FInventoryModelMasterDomain> FInventoryModelMasterDomainPtr;
}
