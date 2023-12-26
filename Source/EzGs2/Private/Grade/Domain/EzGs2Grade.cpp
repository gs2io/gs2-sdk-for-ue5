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

#include "Grade/Domain/EzGs2Grade.h"

namespace Gs2::UE5::Grade::Domain
{

    FEzGs2Grade::FEzGs2Grade(
        Gs2::Grade::Domain::FGs2GradeDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Grade::Domain::Model::FEzNamespaceDomainPtr FEzGs2Grade::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Grade::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }
}
