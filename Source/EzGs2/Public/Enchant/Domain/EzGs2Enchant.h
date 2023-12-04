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
#include "Enchant/Domain/Gs2Enchant.h"
#include "Util/Net/Gs2Connection.h"
#include "Enchant/Domain/Model/Gs2EnchantEzNamespaceDomain.h"

namespace Gs2::UE5::Enchant::Domain
{

    class EZGS2_API FEzGs2Enchant {
        Gs2::Enchant::Domain::FGs2EnchantDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:

        FEzGs2Enchant(
            Gs2::Enchant::Domain::FGs2EnchantDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Enchant::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;
    };
    typedef TSharedPtr<FEzGs2Enchant> FEzGs2EnchantPtr;
}
