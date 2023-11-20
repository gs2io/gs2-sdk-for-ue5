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
#include "SkillTree/Domain/Gs2SkillTree.h"
#include "Util/Profile.h"
#include "SkillTree/Domain/Model/Gs2SkillTreeEzNamespaceDomain.h"

namespace Gs2::UE5::SkillTree::Domain
{

    class EZGS2_API FEzGs2SkillTree {
        Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:

        FEzGs2SkillTree(
            Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::SkillTree::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;
    };
    typedef TSharedPtr<FEzGs2SkillTree> FEzGs2SkillTreePtr;
}
