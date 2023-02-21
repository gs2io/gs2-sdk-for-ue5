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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"
#include "MegaField/Model/Gs2MegaFieldEzVector.h"
#include "Gs2MegaFieldEzSpatialDomain.h"
#include "Gs2MegaFieldEzSpatialGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    class EZGS2_API FEzSpatialGameSessionDomain final :
        public TSharedFromThis<FEzSpatialGameSessionDomain>
    {
        Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> AreaModelName() const;
        TOptional<FString> LayerModelName() const;

        FEzSpatialGameSessionDomain(
            Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FUpdateTask :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomain>>>,
            public TSharedFromThis<FUpdateTask>
        {
            TSharedPtr<FEzSpatialGameSessionDomain> Self;
            Gs2::UE5::MegaField::Model::FEzMyPositionPtr Position;
            TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>> Scopes;

        public:
            explicit FUpdateTask(
                TSharedPtr<FEzSpatialGameSessionDomain> Self,
                Gs2::UE5::MegaField::Model::FEzMyPositionPtr Position,
                TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>> Scopes = TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Domain::Model::FEzSpatialDomain>>>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Gs2::UE5::MegaField::Model::FEzMyPositionPtr Position,
            TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>> Scopes = TOptional<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzScope>>>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzSpatial>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSpatialGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSpatialGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::MegaField::Model::FEzSpatialPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzSpatialGameSessionDomain> FEzSpatialGameSessionDomainPtr;
}
