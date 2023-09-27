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
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValue.h"
#include "Gs2EnchantEzBalanceParameterModelDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeBalanceParameterModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    class EZGS2_API FEzBalanceParameterModelDomain final :
        public TSharedFromThis<FEzBalanceParameterModelDomain>
    {
        Gs2::Enchant::Domain::Model::FBalanceParameterModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> ParameterName() const;

        FEzBalanceParameterModelDomain(
            Gs2::Enchant::Domain::Model::FBalanceParameterModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetBalanceParameterModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enchant::Model::FEzBalanceParameterModel>,
            public TSharedFromThis<FGetBalanceParameterModelTask>
        {
            TSharedPtr<FEzBalanceParameterModelDomain> Self;

        public:
            explicit FGetBalanceParameterModelTask(
                TSharedPtr<FEzBalanceParameterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterModel>> Result
            ) override;
        };
        friend FGetBalanceParameterModelTask;

        TSharedPtr<FAsyncTask<FGetBalanceParameterModelTask>> GetBalanceParameterModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enchant::Model::FEzBalanceParameterModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBalanceParameterModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBalanceParameterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Enchant::Model::FEzBalanceParameterModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBalanceParameterModelDomain> FEzBalanceParameterModelDomainPtr;
}
