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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "ItemSetEntry.h"
#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Inventory/Domain/Gs2Inventory.h"
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

    class GS2INVENTORY_API FItemSetDomain:
        public TSharedFromThis<FItemSetDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inventory::Domain::FGs2InventoryDomainPtr Service;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<int64> OverflowCount;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<int64> GetOverflowCount() const
        {
            return OverflowCount;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
        TOptional<FString> ItemSetName;
    private:

        FString ParentKey;

    public:

        FItemSetDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inventory::Domain::FGs2InventoryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName,
            const TOptional<FString> ItemSetName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FItemSetDomain(
            const FItemSetDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FGetItemSetByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FGetItemSetByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetItemSetByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FGetItemWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FGetItemWithSignatureTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FGetItemWithSignatureByUserIdRequestPtr Request;
        public:
            explicit FGetItemWithSignatureTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FGetItemWithSignatureByUserIdRequestPtr Request
            );

            FGetItemWithSignatureTask(
                const FGetItemWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FGetItemWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetItemWithSignatureTask>> GetItemWithSignature(
            Request::FGetItemWithSignatureByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FAcquireTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FAcquireTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FAcquireItemSetByUserIdRequestPtr Request;
        public:
            explicit FAcquireTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FAcquireItemSetByUserIdRequestPtr Request
            );

            FAcquireTask(
                const FAcquireTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FAcquireTask;

        TSharedPtr<FAsyncTask<FAcquireTask>> Acquire(
            Request::FAcquireItemSetByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FConsumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FConsumeTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FConsumeItemSetByUserIdRequestPtr Request;
        public:
            explicit FConsumeTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FConsumeItemSetByUserIdRequestPtr Request
            );

            FConsumeTask(
                const FConsumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FConsumeTask;

        TSharedPtr<FAsyncTask<FConsumeTask>> Consume(
            Request::FConsumeItemSetByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FDeleteItemSetByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FDeleteItemSetByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteItemSetByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FItemSetDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FVerifyItemSetByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FVerifyItemSetByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyItemSetByUserIdRequestPtr Request
        );

        class GS2INVENTORY_API FAddReferenceOfTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfDomain>,
            public TSharedFromThis<FAddReferenceOfTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
            const Request::FAddReferenceOfByUserIdRequestPtr Request;
        public:
            explicit FAddReferenceOfTask(
                const TSharedPtr<FItemSetDomain>& Self,
                const Request::FAddReferenceOfByUserIdRequestPtr Request
            );

            FAddReferenceOfTask(
                const FAddReferenceOfTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain>> Result
            ) override;
        };
        friend FAddReferenceOfTask;

        TSharedPtr<FAsyncTask<FAddReferenceOfTask>> AddReferenceOf(
            Request::FAddReferenceOfByUserIdRequestPtr Request
        );

        Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfByUserIdIteratorPtr ReferenceOves(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReferenceOves(
            TFunction<void()> Callback
        );

        void UnsubscribeReferenceOves(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain> ReferenceOf(
            const FString ReferenceOf
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FItemSetPtr>>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FItemSetDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FItemSetDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FItemSetEntryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FItemSetDomain> FItemSetDomainPtr;
}
