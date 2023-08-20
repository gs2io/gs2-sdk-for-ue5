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

#include "Inventory/Domain/Model/Gs2InventoryEzBigInventoryDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzBigInventoryDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzBigInventoryDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBigInventoryDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzBigInventoryDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzBigInventoryDomain::FEzBigInventoryDomain(
        Gs2::Inventory::Domain::Model::FBigInventoryDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Inventory::Domain::Model::FEzBigItemDomainPtr FEzBigInventoryDomain::BigItem(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzBigItemDomain>(
            Domain->BigItem(
                ItemName
            ),
            ProfileValue
        );
    }
}
