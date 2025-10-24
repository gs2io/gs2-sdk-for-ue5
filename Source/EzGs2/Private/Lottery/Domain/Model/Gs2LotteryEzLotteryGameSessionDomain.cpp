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

#include "Lottery/Domain/Model/Gs2LotteryEzLotteryGameSessionDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzLotteryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzLotteryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzLotteryGameSessionDomain::LotteryName() const
    {
        return Domain->LotteryName;
    }

    FEzLotteryGameSessionDomain::FEzLotteryGameSessionDomain(
        Gs2::Lottery::Domain::Model::FLotteryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeProbabilitiesIteratorPtr FEzLotteryGameSessionDomain::Probabilities(
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeProbabilitiesIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzLotteryGameSessionDomain::SubscribeProbabilities(TFunction<void()> Callback)
    {
        return Domain->SubscribeProbabilities(
            Callback
        );
    }

    void FEzLotteryGameSessionDomain::UnsubscribeProbabilities(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeProbabilities(
            CallbackId
        );
    }
}
