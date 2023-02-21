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
#include "Experience/Domain/Model/Status.h"
#include "Experience/Model/Gs2ExperienceEzExperienceModel.h"
#include "Experience/Model/Gs2ExperienceEzThreshold.h"
#include "Experience/Model/Gs2ExperienceEzStatus.h"
#include "Gs2ExperienceEzStatusDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    class EZGS2_API FEzStatusDomain final :
        public TSharedFromThis<FEzStatusDomain>
    {
        Gs2::Experience::Domain::Model::FStatusDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ExperienceName() const;
        TOptional<FString> PropertyId() const;

        FEzStatusDomain(
            Gs2::Experience::Domain::Model::FStatusDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Experience::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzStatusDomain> FEzStatusDomainPtr;
}
