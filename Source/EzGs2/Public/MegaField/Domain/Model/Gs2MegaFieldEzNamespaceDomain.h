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
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzPosition.h"
#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"
#include "MegaField/Model/Gs2MegaFieldEzVector.h"
#include "Gs2MegaFieldEzAreaModelDomain.h"
#include "MegaField/Domain/Iterator/Gs2MegaFieldEzDescribeAreaModelsIterator.h"
#include "Gs2MegaFieldEzUserDomain.h"
#include "Gs2MegaFieldEzUserDomain.h"
#include "Gs2MegaFieldEzUserGameSessionDomain.h"
#include "Gs2MegaFieldEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::MegaField::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::MegaField::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeAreaModelsIteratorPtr AreaModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAreaModels(TFunction<void()> Callback);

        void UnsubscribeAreaModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::MegaField::Domain::Model::FEzAreaModelDomainPtr AreaModel(
            const FString AreaModelName
        ) const;

        Gs2::UE5::MegaField::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::MegaField::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::FGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
