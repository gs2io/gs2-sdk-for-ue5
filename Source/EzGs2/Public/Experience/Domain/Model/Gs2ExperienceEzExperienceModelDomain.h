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
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Model/Gs2ExperienceEzExperienceModel.h"
#include "Experience/Model/Gs2ExperienceEzThreshold.h"
#include "Experience/Model/Gs2ExperienceEzStatus.h"
#include "Experience/Model/Gs2ExperienceEzAcquireAction.h"
#include "Experience/Model/Gs2ExperienceEzAcquireActionRate.h"
#include "Experience/Model/Gs2ExperienceEzVerifyActionResult.h"
#include "Experience/Model/Gs2ExperienceEzConsumeActionResult.h"
#include "Experience/Model/Gs2ExperienceEzAcquireActionResult.h"
#include "Experience/Model/Gs2ExperienceEzTransactionResult.h"
#include "Gs2ExperienceEzExperienceModelDomain.h"
#include "Experience/Domain/Iterator/Gs2ExperienceEzDescribeExperienceModelsIterator.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    class EZGS2_API FEzExperienceModelDomain final :
        public TSharedFromThis<FEzExperienceModelDomain>
    {
        Gs2::Experience::Domain::Model::FExperienceModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> ExperienceName() const;

        FEzExperienceModelDomain(
            Gs2::Experience::Domain::Model::FExperienceModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Model::FEzExperienceModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzExperienceModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzExperienceModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Experience::Model::FEzExperienceModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Experience::Model::FEzExperienceModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzExperienceModelDomain> FEzExperienceModelDomainPtr;
}
