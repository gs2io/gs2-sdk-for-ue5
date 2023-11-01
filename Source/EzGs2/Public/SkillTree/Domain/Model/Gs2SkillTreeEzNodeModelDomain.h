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
#include "SkillTree/Domain/Model/NodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeEzNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeEzStatus.h"
#include "SkillTree/Model/Gs2SkillTreeEzConfig.h"
#include "SkillTree/Model/Gs2SkillTreeEzAcquireAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzConsumeAction.h"
#include "Gs2SkillTreeEzNodeModelDomain.h"
#include "SkillTree/Domain/Iterator/Gs2SkillTreeEzDescribeNodeModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    class EZGS2_API FEzNodeModelDomain final :
        public TSharedFromThis<FEzNodeModelDomain>
    {
        Gs2::SkillTree::Domain::Model::FNodeModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> NodeModelName() const;

        FEzNodeModelDomain(
            Gs2::SkillTree::Domain::Model::FNodeModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Model::FEzNodeModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzNodeModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzNodeModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SkillTree::Model::FEzNodeModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::SkillTree::Model::FEzNodeModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzNodeModelDomain> FEzNodeModelDomainPtr;
}
