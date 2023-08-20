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
#include "Inventory/Domain/Model/Namespace.h"
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
#include "Gs2InventoryEzInventoryModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeInventoryModelsIterator.h"
#include "Gs2InventoryEzUserDomain.h"
#include "Gs2InventoryEzUserDomain.h"
#include "Gs2InventoryEzUserGameSessionDomain.h"
#include "Gs2InventoryEzSimpleInventoryModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeSimpleInventoryModelsIterator.h"
#include "Gs2InventoryEzBigInventoryModelDomain.h"
#include "Inventory/Domain/Iterator/Gs2InventoryEzDescribeBigInventoryModelsIterator.h"
#include "Gs2InventoryEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Inventory::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Inventory::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeInventoryModelsIteratorPtr InventoryModels(
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzInventoryModelDomainPtr InventoryModel(
            const FString InventoryName
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleInventoryModelsIteratorPtr SimpleInventoryModels(
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryModelDomainPtr SimpleInventoryModel(
            const FString InventoryName
        ) const;

        Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeBigInventoryModelsIteratorPtr BigInventoryModels(
        ) const;

        Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryModelDomainPtr BigInventoryModel(
            const FString InventoryName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
