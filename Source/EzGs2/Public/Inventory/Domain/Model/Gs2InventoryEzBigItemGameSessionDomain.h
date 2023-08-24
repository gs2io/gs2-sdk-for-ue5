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
#include "Inventory/Domain/Model/BigItemAccessToken.h"
#include "Inventory/Model/Gs2InventoryEzInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzItemModel.h"
#include "Inventory/Model/Gs2InventoryEzInventory.h"
#include "Inventory/Model/Gs2InventoryEzItemSet.h"
#include "Inventory/Model/Gs2InventoryEzSimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItemModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItem.h"
#include "Inventory/Model/Gs2InventoryEzBigInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItemModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItem.h"
#include "Inventory/Model/Gs2InventoryEzBigInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItemModel.h"
#include "Inventory/Model/Gs2InventoryEzBigItem.h"
#include "Inventory/Model/Gs2InventoryEzConsumeCount.h"
#include "Inventory/Model/Gs2InventoryEzAcquireCount.h"
#include "Gs2InventoryEzBigItemGameSessionDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeBigItemsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzBigItemGameSessionDomain final :
        public TSharedFromThis<FEzBigItemGameSessionDomain>
    {
        Gs2::Inventory::Domain::Model::FBigItemAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> InventoryName() const;
        TOptional<FString> ItemName() const;

        FEzBigItemGameSessionDomain(
            Gs2::Inventory::Domain::Model::FBigItemAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetBigItemTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzBigItem>,
            public TSharedFromThis<FGetBigItemTask>
        {
            TSharedPtr<FEzBigItemGameSessionDomain> Self;

        public:
            explicit FGetBigItemTask(
                TSharedPtr<FEzBigItemGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigItem>> Result
            ) override;
        };
        friend FGetBigItemTask;

        TSharedPtr<FAsyncTask<FGetBigItemTask>> GetBigItem(
        );

        class FConsumeBigItemTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomain>,
            public TSharedFromThis<FConsumeBigItemTask>
        {
            TSharedPtr<FEzBigItemGameSessionDomain> Self;
            FString ConsumeCount;

        public:
            explicit FConsumeBigItemTask(
                TSharedPtr<FEzBigItemGameSessionDomain> Self,
                FString ConsumeCount
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomain>> Result
            ) override;
        };
        friend FConsumeBigItemTask;

        TSharedPtr<FAsyncTask<FConsumeBigItemTask>> ConsumeBigItem(
            FString ConsumeCount
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzBigItem>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBigItemGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBigItemGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigItemPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzBigItemGameSessionDomain> FEzBigItemGameSessionDomainPtr;
}