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

    class GS2INVENTORY_API FReferenceOfAccessTokenDomain:
        public TSharedFromThis<FReferenceOfAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inventory::Domain::FGs2InventoryDomainPtr Service;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> InventoryName;
        TOptional<FString> ItemName;
        TOptional<FString> ItemSetName;
        TOptional<FString> ReferenceOf;
    private:

        FString ParentKey;

    public:

        FReferenceOfAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inventory::Domain::FGs2InventoryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> InventoryName,
            const TOptional<FString> ItemName,
            const TOptional<FString> ItemSetName,
            const TOptional<FString> ReferenceOf
            // ReSharper disable once CppMemberInitializersOrder
        );

        FReferenceOfAccessTokenDomain(
            const FReferenceOfAccessTokenDomain& From
        );

        class GS2INVENTORY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<TArray<FString>>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FReferenceOfAccessTokenDomain> Self;
            const Request::FGetReferenceOfRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
                const Request::FGetReferenceOfRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<FString>>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetReferenceOfRequestPtr Request
        );

        class GS2INVENTORY_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FReferenceOfAccessTokenDomain> Self;
            const Request::FVerifyReferenceOfRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
                const Request::FVerifyReferenceOfRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyReferenceOfRequestPtr Request
        );

        class GS2INVENTORY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FReferenceOfAccessTokenDomain> Self;
            const Request::FDeleteReferenceOfRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
                const Request::FDeleteReferenceOfRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteReferenceOfRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> InventoryName,
            TOptional<FString> ItemName,
            TOptional<FString> ItemSetName,
            TOptional<FString> ReferenceOf,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ReferenceOf
        );

        class GS2INVENTORY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inventory::Model::FItemSet>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FReferenceOfAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FReferenceOfAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FItemSet>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inventory::Model::FReferenceOfPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FReferenceOfAccessTokenDomain> FReferenceOfAccessTokenDomainPtr;
}
