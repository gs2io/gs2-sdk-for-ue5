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
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"
#include "MegaField/Model/Gs2MegaFieldEzVector.h"
#include "Gs2MegaFieldEzSpatialDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    class EZGS2_API FEzSpatialDomain final :
        public TSharedFromThis<FEzSpatialDomain>
    {
        Gs2::MegaField::Domain::Model::FSpatialDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> AreaModelName() const;
        TOptional<FString> LayerModelName() const;

        FEzSpatialDomain(
            Gs2::MegaField::Domain::Model::FSpatialDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzSpatial>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSpatialDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSpatialDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::MegaField::Model::FEzSpatialPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzSpatialDomain> FEzSpatialDomainPtr;
}
