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

#include "Inventory/Domain/Model/Gs2InventoryEzUserGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Inventory::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeInventoriesIteratorPtr FEzUserGameSessionDomain::Inventories(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeInventoriesIterator>(
            Domain->Inventories(
            )
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzInventoryGameSessionDomainPtr FEzUserGameSessionDomain::Inventory(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzInventoryGameSessionDomain>(
            Domain->Inventory(
                InventoryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryGameSessionDomainPtr FEzUserGameSessionDomain::SimpleInventory(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryGameSessionDomain>(
            Domain->SimpleInventory(
                InventoryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryGameSessionDomainPtr FEzUserGameSessionDomain::BigInventory(
        const FString InventoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigInventoryGameSessionDomain>(
            Domain->BigInventory(
                InventoryName
            ),
            ProfileValue
        );
    }
}
