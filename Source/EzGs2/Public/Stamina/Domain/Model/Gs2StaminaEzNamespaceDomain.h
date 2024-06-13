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
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"
#include "Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverIntervalTable.h"
#include "Stamina/Model/Gs2StaminaEzRecoverValueTable.h"
#include "Stamina/Model/Gs2StaminaEzStamina.h"
#include "Gs2StaminaEzStaminaModelDomain.h"
#include "Stamina/Domain/Iterator/Gs2StaminaEzDescribeStaminaModelsIterator.h"
#include "Gs2StaminaEzUserDomain.h"
#include "Gs2StaminaEzUserDomain.h"
#include "Gs2StaminaEzUserGameSessionDomain.h"
#include "Gs2StaminaEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Stamina::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Stamina::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Stamina::Domain::Iterator::FEzDescribeStaminaModelsIteratorPtr StaminaModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStaminaModels(TFunction<void()> Callback);

        void UnsubscribeStaminaModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Stamina::Domain::Model::FEzStaminaModelDomainPtr StaminaModel(
            const FString StaminaName
        ) const;

        Gs2::UE5::Stamina::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Stamina::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
