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

#include "Inventory/Domain/Model/Gs2InventoryEzReferenceOfGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzReferenceOfGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzReferenceOfGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzReferenceOfGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    TOptional<FString> FEzReferenceOfGameSessionDomain::ItemName() const
    {
        return Domain->ItemName;
    }

    TOptional<FString> FEzReferenceOfGameSessionDomain::ItemSetName() const
    {
        return Domain->ItemSetName;
    }

    TOptional<FString> FEzReferenceOfGameSessionDomain::ReferenceOf() const
    {
        return Domain->ReferenceOf;
    }

    FEzReferenceOfGameSessionDomain::FEzReferenceOfGameSessionDomain(
        Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }
}
