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
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"
#include "MegaField/Model/Gs2MegaFieldEzVector.h"
#include "Gs2MegaFieldEzLayerModelDomain.h"
#include "MegaField/Domain/Iterator/Gs2MegaFieldEzDescribeLayerModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    class EZGS2_API FEzLayerModelDomain final :
        public TSharedFromThis<FEzLayerModelDomain>
    {
        Gs2::MegaField::Domain::Model::FLayerModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> AreaModelName() const;
        TOptional<FString> LayerModelName() const;

        FEzLayerModelDomain(
            Gs2::MegaField::Domain::Model::FLayerModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetLayerModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzLayerModel>,
            public TSharedFromThis<FGetLayerModelTask>
        {
            TSharedPtr<FEzLayerModelDomain> Self;

        public:
            explicit FGetLayerModelTask(
                TSharedPtr<FEzLayerModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>> Result
            ) override;
        };
        friend FGetLayerModelTask;

        TSharedPtr<FAsyncTask<FGetLayerModelTask>> GetLayerModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzLayerModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzLayerModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzLayerModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzLayerModelDomain> FEzLayerModelDomainPtr;
}
