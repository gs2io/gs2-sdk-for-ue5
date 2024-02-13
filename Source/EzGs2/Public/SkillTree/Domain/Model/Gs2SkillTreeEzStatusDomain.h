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
#include "SkillTree/Domain/Model/Status.h"
#include "SkillTree/Model/Gs2SkillTreeEzNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeEzStatus.h"
#include "SkillTree/Model/Gs2SkillTreeEzConfig.h"
#include "SkillTree/Model/Gs2SkillTreeEzAcquireAction.h"
#include "SkillTree/Model/Gs2SkillTreeEzConsumeAction.h"
#include "Gs2SkillTreeEzStatusDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    class EZGS2_API FEzStatusDomain final :
        public TSharedFromThis<FEzStatusDomain>
    {
        Gs2::SkillTree::Domain::Model::FStatusDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> PropertyId() const;

        FEzStatusDomain(
            Gs2::SkillTree::Domain::Model::FStatusDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SkillTree::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SkillTree::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::SkillTree::Model::FEzStatusPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzStatusDomain> FEzStatusDomainPtr;
}
