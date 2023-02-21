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
#include "Gs2Datastore/Public/Datastore/Domain/Gs2Datastore.h"
#include "Util/Profile.h"
#include "Datastore/Domain/Model/Gs2DatastoreEzNamespaceDomain.h"

namespace Gs2::UE5::Datastore::Domain
{

    class EZGS2_API FEzGs2Datastore {
        Gs2::Datastore::Domain::FGs2DatastoreDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:

        FEzGs2Datastore(
            Gs2::Datastore::Domain::FGs2DatastoreDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Datastore::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;
    };
    typedef TSharedPtr<FEzGs2Datastore> FEzGs2DatastorePtr;
}
