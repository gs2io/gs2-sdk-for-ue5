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
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Model/Gs2EnhanceEzRateModel.h"
#include "Enhance/Model/Gs2EnhanceEzProgress.h"
#include "Enhance/Model/Gs2EnhanceEzConfig.h"
#include "Enhance/Model/Gs2EnhanceEzMaterial.h"
#include "Gs2EnhanceEzProgressDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    class EZGS2_API FEzProgressDomain final :
        public TSharedFromThis<FEzProgressDomain>
    {
        Gs2::Enhance::Domain::Model::FProgressDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<int64> AcquireExperience() const;
        TOptional<float> BonusRate() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzProgressDomain(
            Gs2::Enhance::Domain::Model::FProgressDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enhance::Model::FEzProgress>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzProgressDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzProgressDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enhance::Model::FEzProgressPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzProgressDomain> FEzProgressDomainPtr;
}
