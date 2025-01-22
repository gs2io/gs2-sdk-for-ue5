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
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"
#include "Lottery/Model/Gs2LotteryEzProbability.h"
#include "Lottery/Model/Gs2LotteryEzAcquireAction.h"
#include "Lottery/Model/Gs2LotteryEzDrawnPrize.h"
#include "Lottery/Model/Gs2LotteryEzBoxItem.h"
#include "Lottery/Model/Gs2LotteryEzBoxItems.h"
#include "Lottery/Model/Gs2LotteryEzConfig.h"
#include "Lottery/Model/Gs2LotteryEzVerifyActionResult.h"
#include "Lottery/Model/Gs2LotteryEzConsumeActionResult.h"
#include "Lottery/Model/Gs2LotteryEzAcquireActionResult.h"
#include "Lottery/Model/Gs2LotteryEzTransactionResult.h"
#include "Lottery/Domain/Iterator/Gs2LotteryEzDescribeProbabilitiesIterator.h"
#include "Gs2LotteryEzLotteryGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    class EZGS2_API FEzLotteryGameSessionDomain final :
        public TSharedFromThis<FEzLotteryGameSessionDomain>
    {
        Gs2::Lottery::Domain::Model::FLotteryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> LotteryName() const;

        FEzLotteryGameSessionDomain(
            Gs2::Lottery::Domain::Model::FLotteryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeProbabilitiesIteratorPtr Probabilities(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeProbabilities(TFunction<void()> Callback);

        void UnsubscribeProbabilities(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzLotteryGameSessionDomain> FEzLotteryGameSessionDomainPtr;
}
