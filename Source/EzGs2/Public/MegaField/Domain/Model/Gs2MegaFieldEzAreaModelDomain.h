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
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"
#include "MegaField/Model/Gs2MegaFieldEzVector.h"
#include "Gs2MegaFieldEzLayerModelDomain.h"
#include "MegaField/Domain/Iterator/Gs2MegaFieldEzDescribeLayerModelsIterator.h"
#include "Gs2MegaFieldEzAreaModelDomain.h"
#include "MegaField/Domain/Iterator/Gs2MegaFieldEzDescribeAreaModelsIterator.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    class EZGS2_API FEzAreaModelDomain final :
        public TSharedFromThis<FEzAreaModelDomain>
    {
        Gs2::MegaField::Domain::Model::FAreaModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> AreaModelName() const;

        FEzAreaModelDomain(
            Gs2::MegaField::Domain::Model::FAreaModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeLayerModelsIteratorPtr LayerModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLayerModels(TFunction<void()> Callback);

        void UnsubscribeLayerModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::MegaField::Domain::Model::FEzLayerModelDomainPtr LayerModel(
            const FString LayerModelName
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzAreaModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAreaModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAreaModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::MegaField::Model::FEzAreaModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::MegaField::Model::FEzAreaModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAreaModelDomain> FEzAreaModelDomainPtr;
}
