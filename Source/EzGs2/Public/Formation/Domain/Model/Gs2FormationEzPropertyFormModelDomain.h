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
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Model/Gs2FormationEzFormModel.h"
#include "Formation/Model/Gs2FormationEzMoldModel.h"
#include "Formation/Model/Gs2FormationEzPropertyFormModel.h"
#include "Formation/Model/Gs2FormationEzMold.h"
#include "Formation/Model/Gs2FormationEzForm.h"
#include "Formation/Model/Gs2FormationEzPropertyForm.h"
#include "Formation/Model/Gs2FormationEzSlot.h"
#include "Formation/Model/Gs2FormationEzSlotModel.h"
#include "Formation/Model/Gs2FormationEzSlotWithSignature.h"
#include "Formation/Model/Gs2FormationEzAcquireActionConfig.h"
#include "Formation/Model/Gs2FormationEzConfig.h"
#include "Formation/Model/Gs2FormationEzAcquireAction.h"
#include "Gs2FormationEzPropertyFormModelDomain.h"
#include "Formation/Domain/Iterator/Gs2FormationEzDescribePropertyFormModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzPropertyFormModelDomain final :
        public TSharedFromThis<FEzPropertyFormModelDomain>
    {
        Gs2::Formation::Domain::Model::FPropertyFormModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> PropertyFormModelName() const;

        FEzPropertyFormModelDomain(
            Gs2::Formation::Domain::Model::FPropertyFormModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetPropertyFormModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzPropertyFormModel>,
            public TSharedFromThis<FGetPropertyFormModelTask>
        {
            TSharedPtr<FEzPropertyFormModelDomain> Self;

        public:
            explicit FGetPropertyFormModelTask(
                TSharedPtr<FEzPropertyFormModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormModel>> Result
            ) override;
        };
        friend FGetPropertyFormModelTask;

        TSharedPtr<FAsyncTask<FGetPropertyFormModelTask>> GetPropertyFormModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzPropertyFormModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPropertyFormModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPropertyFormModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzPropertyFormModelDomain> FEzPropertyFormModelDomainPtr;
}