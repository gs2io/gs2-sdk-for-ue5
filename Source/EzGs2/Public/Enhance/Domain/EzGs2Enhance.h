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
#include "Gs2Enhance/Public/Enhance/Domain/Gs2Enhance.h"
#include "Util/Profile.h"
#include "Enhance/Domain/Model/Gs2EnhanceEzNamespaceDomain.h"

namespace Gs2::UE5::Enhance::Domain
{

    class EZGS2_API FEzGs2Enhance {
        Gs2::Enhance::Domain::FGs2EnhanceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:

        FEzGs2Enhance(
            Gs2::Enhance::Domain::FGs2EnhanceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Enhance::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;
    };
    typedef TSharedPtr<FEzGs2Enhance> FEzGs2EnhancePtr;
}
