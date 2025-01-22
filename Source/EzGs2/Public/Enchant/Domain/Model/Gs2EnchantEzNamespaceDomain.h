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
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantEzRarityParameterValue.h"
#include "Enchant/Model/Gs2EnchantEzVerifyActionResult.h"
#include "Enchant/Model/Gs2EnchantEzConsumeActionResult.h"
#include "Enchant/Model/Gs2EnchantEzAcquireActionResult.h"
#include "Enchant/Model/Gs2EnchantEzTransactionResult.h"
#include "Gs2EnchantEzBalanceParameterModelDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeBalanceParameterModelsIterator.h"
#include "Gs2EnchantEzRarityParameterModelDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeRarityParameterModelsIterator.h"
#include "Gs2EnchantEzUserDomain.h"
#include "Gs2EnchantEzUserDomain.h"
#include "Gs2EnchantEzUserGameSessionDomain.h"
#include "Gs2EnchantEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Enchant::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Enchant::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterModelsIteratorPtr BalanceParameterModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBalanceParameterModels(TFunction<void()> Callback);

        void UnsubscribeBalanceParameterModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterModelDomainPtr BalanceParameterModel(
            const FString ParameterName
        ) const;

        Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterModelsIteratorPtr RarityParameterModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRarityParameterModels(TFunction<void()> Callback);

        void UnsubscribeRarityParameterModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterModelDomainPtr RarityParameterModel(
            const FString ParameterName
        ) const;

        Gs2::UE5::Enchant::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Enchant::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
