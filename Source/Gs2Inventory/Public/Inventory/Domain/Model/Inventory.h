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

    class GS2INVENTORY_API FInventoryDomain:
        public TSharedFromThis<FInventoryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inventory::Domain::FGs2InventoryDomainPtr Service;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

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
            const Core::Domain::FGs2Ptr& Gs2,
            const Inventory::Domain::FGs2InventoryDomainPtr& Service,
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
                const TSharedPtr<FInventoryDomain>& Self,
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
                const TSharedPtr<FInventoryDomain>& Self,
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
                const TSharedPtr<FInventoryDomain>& Self,
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
                const TSharedPtr<FInventoryDomain>& Self,
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

        class GS2INVENTORY_API FVerifyCurrentMaxCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FInventoryDomain>,
            public TSharedFromThis<FVerifyCurrentMaxCapacityTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request;
        public:
            explicit FVerifyCurrentMaxCapacityTask(
                const TSharedPtr<FInventoryDomain>& Self,
                const Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request
            );

            FVerifyCurrentMaxCapacityTask(
                const FVerifyCurrentMaxCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryDomain>> Result
            ) override;
        };
        friend FVerifyCurrentMaxCapacityTask;

        TSharedPtr<FAsyncTask<FVerifyCurrentMaxCapacityTask>> VerifyCurrentMaxCapacity(
            Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FAcquireItemSetWithGradeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FAcquireItemSetWithGradeTask>
        {
            const TSharedPtr<FInventoryDomain> Self;
            const Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request;
        public:
            explicit FAcquireItemSetWithGradeTask(
                const TSharedPtr<FInventoryDomain>& Self,
                const Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request
            );

            FAcquireItemSetWithGradeTask(
                const FAcquireItemSetWithGradeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FAcquireItemSetWithGradeTask;

        TSharedPtr<FAsyncTask<FAcquireItemSetWithGradeTask>> AcquireItemSetWithGrade(
            Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeItemSetsByUserIdIteratorPtr ItemSets(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeItemSets(
            TFunction<void()> Callback
        );

        void UnsubscribeItemSets(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain> ItemSet(
            const FString ItemName,
            const TOptional<FString> ItemSetName = TOptional<FString>()
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

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FInventoryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FInventoryDomain> FInventoryDomainPtr;
}
