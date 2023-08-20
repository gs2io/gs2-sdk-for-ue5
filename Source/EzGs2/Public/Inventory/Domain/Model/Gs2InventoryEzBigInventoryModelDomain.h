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
#include "Inventory/Domain/Model/BigInventoryModel.h"
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
#include "Gs2InventoryEzBigItemModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeBigItemModelsIterator.h"
#include "Gs2InventoryEzBigInventoryModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeBigInventoryModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzBigInventoryModelDomain final :
        public TSharedFromThis<FEzBigInventoryModelDomain>
    {
        Gs2::Inventory::Domain::Model::FBigInventoryModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> InventoryName() const;

        FEzBigInventoryModelDomain(
            Gs2::Inventory::Domain::Model::FBigInventoryModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetBigInventoryModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzBigInventoryModel>,
            public TSharedFromThis<FGetBigInventoryModelTask>
        {
            TSharedPtr<FEzBigInventoryModelDomain> Self;

        public:
            explicit FGetBigInventoryModelTask(
                TSharedPtr<FEzBigInventoryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigInventoryModel>> Result
            ) override;
        };
        friend FGetBigInventoryModelTask;

        TSharedPtr<FAsyncTask<FGetBigInventoryModelTask>> GetBigInventoryModel(
        );

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemModelsIteratorPtr BigItemModels(
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzBigItemModelDomainPtr BigItemModel(
            const FString ItemName
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzBigInventoryModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBigInventoryModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBigInventoryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Inventory::Model::FEzBigInventoryModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzBigInventoryModelDomain> FEzBigInventoryModelDomainPtr;
}
