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
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"
#include "Showcase/Model/Gs2ShowcaseEzShowcase.h"
#include "Showcase/Model/Gs2ShowcaseEzDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzRandomDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseEzConfig.h"
#include "Showcase/Model/Gs2ShowcaseEzConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseEzAcquireAction.h"
#include "Gs2ShowcaseEzDisplayItemDomain.h"
#include "Gs2ShowcaseEzShowcaseDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    class EZGS2_API FEzShowcaseDomain final :
        public TSharedFromThis<FEzShowcaseDomain>
    {
        Gs2::Showcase::Domain::Model::FShowcaseDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ShowcaseName() const;

        FEzShowcaseDomain(
            Gs2::Showcase::Domain::Model::FShowcaseDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemDomainPtr DisplayItem(
            const FString DisplayItemId
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Showcase::Model::FEzShowcase>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzShowcaseDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzShowcaseDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcasePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzShowcaseDomain> FEzShowcaseDomainPtr;
}
