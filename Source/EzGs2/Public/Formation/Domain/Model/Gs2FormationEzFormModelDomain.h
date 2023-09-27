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
#include "Formation/Domain/Model/FormModel.h"
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
#include "Gs2FormationEzFormModelDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    class EZGS2_API FEzFormModelDomain final :
        public TSharedFromThis<FEzFormModelDomain>
    {
        Gs2::Formation::Domain::Model::FFormModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> MoldModelName() const;
        TOptional<FString> FormModelName() const;

        FEzFormModelDomain(
            Gs2::Formation::Domain::Model::FFormModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetFormModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzFormModel>,
            public TSharedFromThis<FGetFormModelTask>
        {
            TSharedPtr<FEzFormModelDomain> Self;

        public:
            explicit FGetFormModelTask(
                TSharedPtr<FEzFormModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel>> Result
            ) override;
        };
        friend FGetFormModelTask;

        TSharedPtr<FAsyncTask<FGetFormModelTask>> GetFormModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzFormModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzFormModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzFormModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzFormModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzFormModelDomain> FEzFormModelDomainPtr;
}
