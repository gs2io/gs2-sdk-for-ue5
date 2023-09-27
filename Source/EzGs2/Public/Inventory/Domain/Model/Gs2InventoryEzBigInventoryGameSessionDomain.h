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
#include "Inventory/Domain/Model/BigInventoryAccessToken.h"
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
#include "Gs2InventoryEzBigInventoryGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzBigInventoryGameSessionDomain final :
        public TSharedFromThis<FEzBigInventoryGameSessionDomain>
    {
        Gs2::Inventory::Domain::Model::FBigInventoryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> InventoryName() const;

        FEzBigInventoryGameSessionDomain(
            Gs2::Inventory::Domain::Model::FBigInventoryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigItemsIteratorPtr BigItems(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBigItems(TFunction<void()> Callback);

        void UnsubscribeBigItems(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomainPtr BigItem(
            const FString ItemName
        ) const;

    };
    typedef TSharedPtr<FEzBigInventoryGameSessionDomain> FEzBigInventoryGameSessionDomainPtr;
}
