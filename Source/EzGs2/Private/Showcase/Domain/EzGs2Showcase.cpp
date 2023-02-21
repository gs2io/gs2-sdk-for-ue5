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

#include "Showcase/Domain/EzGs2Showcase.h"

namespace Gs2::UE5::Showcase::Domain
{

    FEzGs2Showcase::FEzGs2Showcase(
        Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Showcase::Domain::Model::FEzNamespaceDomainPtr FEzGs2Showcase::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ProfileValue
        );
    }
}
