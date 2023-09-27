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
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"
#include "Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverIntervalTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverValueTable.h"
#include "Stamina/Model/Gs2StaminaEzStamina.h"
#include "Gs2StaminaEzStaminaModelDomain.h"
#include "Stamina/Domain/Iterator/Gs2StaminaEzDescribeStaminaModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    class EZGS2_API FEzStaminaModelDomain final :
        public TSharedFromThis<FEzStaminaModelDomain>
    {
        Gs2::Stamina::Domain::Model::FStaminaModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> StaminaName() const;

        FEzStaminaModelDomain(
            Gs2::Stamina::Domain::Model::FStaminaModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetStaminaModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Model::FEzStaminaModel>,
            public TSharedFromThis<FGetStaminaModelTask>
        {
            TSharedPtr<FEzStaminaModelDomain> Self;

        public:
            explicit FGetStaminaModelTask(
                TSharedPtr<FEzStaminaModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaModel>> Result
            ) override;
        };
        friend FGetStaminaModelTask;

        TSharedPtr<FAsyncTask<FGetStaminaModelTask>> GetStaminaModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Model::FEzStaminaModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStaminaModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStaminaModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Stamina::Model::FEzStaminaModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzStaminaModelDomain> FEzStaminaModelDomainPtr;
}
