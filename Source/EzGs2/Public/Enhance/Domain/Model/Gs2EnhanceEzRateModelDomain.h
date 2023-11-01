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
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Model/Gs2EnhanceEzRateModel.h"
#include "Enhance/Model/Gs2EnhanceEzProgress.h"
#include "Enhance/Model/Gs2EnhanceEzConfig.h"
#include "Enhance/Model/Gs2EnhanceEzMaterial.h"
#include "Gs2EnhanceEzRateModelDomain.h"
#include "Enhance/Domain/Iterator/Gs2EnhanceEzDescribeRateModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    class EZGS2_API FEzRateModelDomain final :
        public TSharedFromThis<FEzRateModelDomain>
    {
        Gs2::Enhance::Domain::Model::FRateModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RateName() const;

        FEzRateModelDomain(
            Gs2::Enhance::Domain::Model::FRateModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Model::FEzRateModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRateModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRateModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enhance::Model::FEzRateModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Enhance::Model::FEzRateModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzRateModelDomain> FEzRateModelDomainPtr;
}
