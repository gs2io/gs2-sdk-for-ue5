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
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Model/Gs2InventoryEzInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzItemModel.h"
#include "Inventory/Model/Gs2InventoryEzInventory.h"
#include "Inventory/Model/Gs2InventoryEzItemSet.h"
#include "Inventory/Model/Gs2InventoryEzSimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItemModel.h"
#include "Inventory/Model/Gs2InventoryEzSimpleItem.h"
#include "Inventory/Model/Gs2InventoryEzConsumeCount.h"
#include "Inventory/Model/Gs2InventoryEzAcquireCount.h"
#include "Gs2InventoryEzItemModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeItemModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzItemModelDomain final :
        public TSharedFromThis<FEzItemModelDomain>
    {
        Gs2::Inventory::Domain::Model::FItemModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> InventoryName() const;
        TOptional<FString> ItemName() const;

        FEzItemModelDomain(
            Gs2::Inventory::Domain::Model::FItemModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetItemModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzItemModel>,
            public TSharedFromThis<FGetItemModelTask>
        {
            TSharedPtr<FEzItemModelDomain> Self;

        public:
            explicit FGetItemModelTask(
                TSharedPtr<FEzItemModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemModel>> Result
            ) override;
        };
        friend FGetItemModelTask;

        TSharedPtr<FAsyncTask<FGetItemModelTask>> GetItemModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzItemModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzItemModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzItemModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzItemModelDomain> FEzItemModelDomainPtr;
}
