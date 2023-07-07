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

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Domain/Model/SimpleInventoryAccessToken.h"
#include "Inventory/Model/Gs2InventoryEzInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzItemModel.h"
#include "Inventory/Model/Gs2InventoryEzInventory.h"
#include "Inventory/Model/Gs2InventoryEzItemSet.h"
#include "Inventory/Model/Gs2InventoryEzSimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItemModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItem.h"
#include "Inventory/Model/Gs2InventoryEzConsumeCount.h"
#include "Inventory/Model/Gs2InventoryEzAcquireCount.h"
#include "Gs2InventoryEzSimpleItemGameSessionDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeSimpleItemsIterator.h"
#include "Gs2InventoryEzSimpleInventoryGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzSimpleInventoryGameSessionDomain final :
        public TSharedFromThis<FEzSimpleInventoryGameSessionDomain>
    {
        Gs2::Inventory::Domain::Model::FSimpleInventoryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> InventoryName() const;

        FEzSimpleInventoryGameSessionDomain(
            Gs2::Inventory::Domain::Model::FSimpleInventoryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FConsumeSimpleItemsTask :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>>>,
            public TSharedFromThis<FConsumeSimpleItemsTask>
        {
            TSharedPtr<FEzSimpleInventoryGameSessionDomain> Self;
            TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzConsumeCount>> ConsumeCounts;

        public:
            explicit FConsumeSimpleItemsTask(
                TSharedPtr<FEzSimpleInventoryGameSessionDomain> Self,
                TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzConsumeCount>> ConsumeCounts
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>>>> Result
            ) override;
        };
        friend FConsumeSimpleItemsTask;

        TSharedPtr<FAsyncTask<FConsumeSimpleItemsTask>> ConsumeSimpleItems(
            TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzConsumeCount>> ConsumeCounts
        );

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleItemsIteratorPtr SimpleItems(
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomainPtr SimpleItem(
            const FString ItemName
        ) const;

    };
    typedef TSharedPtr<FEzSimpleInventoryGameSessionDomain> FEzSimpleInventoryGameSessionDomainPtr;
}
