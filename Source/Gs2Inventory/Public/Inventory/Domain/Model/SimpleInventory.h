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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Inventory::Domain
{
    class FGs2InventoryDomain;
    typedef TSharedPtr<FGs2InventoryDomain> FGs2InventoryDomainPtr;
}

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

    class GS2INVENTORY_API FSimpleInventoryDomain:
        public TSharedFromThis<FSimpleInventoryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inventory::Domain::FGs2InventoryDomainPtr Service;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
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

        FSimpleInventoryDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inventory::Domain::FGs2InventoryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> InventoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSimpleInventoryDomain(
            const FSimpleInventoryDomain& From
        );

        class GS2INVENTORY_API FAcquireSimpleItemsTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>,
            public TSharedFromThis<FAcquireSimpleItemsTask>
        {
            const TSharedPtr<FSimpleInventoryDomain> Self;
            const Request::FAcquireSimpleItemsByUserIdRequestPtr Request;
        public:
            explicit FAcquireSimpleItemsTask(
                const TSharedPtr<FSimpleInventoryDomain>& Self,
                const Request::FAcquireSimpleItemsByUserIdRequestPtr Request
            );

            FAcquireSimpleItemsTask(
                const FAcquireSimpleItemsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
            ) override;
        };
        friend FAcquireSimpleItemsTask;

        TSharedPtr<FAsyncTask<FAcquireSimpleItemsTask>> AcquireSimpleItems(
            Request::FAcquireSimpleItemsByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FConsumeSimpleItemsTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>,
            public TSharedFromThis<FConsumeSimpleItemsTask>
        {
            const TSharedPtr<FSimpleInventoryDomain> Self;
            const Request::FConsumeSimpleItemsByUserIdRequestPtr Request;
        public:
            explicit FConsumeSimpleItemsTask(
                const TSharedPtr<FSimpleInventoryDomain>& Self,
                const Request::FConsumeSimpleItemsByUserIdRequestPtr Request
            );

            FConsumeSimpleItemsTask(
                const FConsumeSimpleItemsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
            ) override;
        };
        friend FConsumeSimpleItemsTask;

        TSharedPtr<FAsyncTask<FConsumeSimpleItemsTask>> ConsumeSimpleItems(
            Request::FConsumeSimpleItemsByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FSetSimpleItemsTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>,
            public TSharedFromThis<FSetSimpleItemsTask>
        {
            const TSharedPtr<FSimpleInventoryDomain> Self;
            const Request::FSetSimpleItemsByUserIdRequestPtr Request;
        public:
            explicit FSetSimpleItemsTask(
                const TSharedPtr<FSimpleInventoryDomain>& Self,
                const Request::FSetSimpleItemsByUserIdRequestPtr Request
            );

            FSetSimpleItemsTask(
                const FSetSimpleItemsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
            ) override;
        };
        friend FSetSimpleItemsTask;

        TSharedPtr<FAsyncTask<FSetSimpleItemsTask>> SetSimpleItems(
            Request::FSetSimpleItemsByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteSimpleItemsTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FSimpleInventoryDomain>,
            public TSharedFromThis<FDeleteSimpleItemsTask>
        {
            const TSharedPtr<FSimpleInventoryDomain> Self;
            const Request::FDeleteSimpleItemsByUserIdRequestPtr Request;
        public:
            explicit FDeleteSimpleItemsTask(
                const TSharedPtr<FSimpleInventoryDomain>& Self,
                const Request::FDeleteSimpleItemsByUserIdRequestPtr Request
            );

            FDeleteSimpleItemsTask(
                const FDeleteSimpleItemsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryDomain>> Result
            ) override;
        };
        friend FDeleteSimpleItemsTask;

        TSharedPtr<FAsyncTask<FDeleteSimpleItemsTask>> DeleteSimpleItems(
            Request::FDeleteSimpleItemsByUserIdRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemsByUserIdIteratorPtr SimpleItems(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSimpleItems(
            TFunction<void()> Callback
        );

        void UnsubscribeSimpleItems(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain> SimpleItem(
            const FString ItemName
        );

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
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FSimpleInventory>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSimpleInventoryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSimpleInventoryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleInventory>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FSimpleInventoryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSimpleInventoryDomain> FSimpleInventoryDomainPtr;
}
