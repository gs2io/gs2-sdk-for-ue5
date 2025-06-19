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
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
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
#include "Gs2EnchantEzBalanceParameterStatusGameSessionDomain.h"
#include "Enchant/Domain/Iterator/Gs2EnchantEzDescribeBalanceParameterStatusesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    class EZGS2_API FEzBalanceParameterStatusGameSessionDomain final :
        public TSharedFromThis<FEzBalanceParameterStatusGameSessionDomain>
    {
        Gs2::Enchant::Domain::Model::FBalanceParameterStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ParameterName() const;
        TOptional<FString> PropertyId() const;

        FEzBalanceParameterStatusGameSessionDomain(
            Gs2::Enchant::Domain::Model::FBalanceParameterStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Enchant::Model::FEzBalanceParameterStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBalanceParameterStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBalanceParameterStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Enchant::Model::FEzBalanceParameterStatusPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBalanceParameterStatusGameSessionDomain> FEzBalanceParameterStatusGameSessionDomainPtr;
}
