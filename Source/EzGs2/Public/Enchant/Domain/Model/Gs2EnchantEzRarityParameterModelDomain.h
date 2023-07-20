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
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValue.h"
#include "Gs2EnchantEzRarityParameterModelDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeRarityParameterModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    class EZGS2_API FEzRarityParameterModelDomain final :
        public TSharedFromThis<FEzRarityParameterModelDomain>
    {
        Gs2::Enchant::Domain::Model::FRarityParameterModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> ParameterName() const;

        FEzRarityParameterModelDomain(
            Gs2::Enchant::Domain::Model::FRarityParameterModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetRarityParameterModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enchant::Model::FEzRarityParameterModel>,
            public TSharedFromThis<FGetRarityParameterModelTask>
        {
            TSharedPtr<FEzRarityParameterModelDomain> Self;

        public:
            explicit FGetRarityParameterModelTask(
                TSharedPtr<FEzRarityParameterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterModel>> Result
            ) override;
        };
        friend FGetRarityParameterModelTask;

        TSharedPtr<FAsyncTask<FGetRarityParameterModelTask>> GetRarityParameterModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enchant::Model::FEzRarityParameterModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRarityParameterModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRarityParameterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzRarityParameterModelDomain> FEzRarityParameterModelDomainPtr;
}
