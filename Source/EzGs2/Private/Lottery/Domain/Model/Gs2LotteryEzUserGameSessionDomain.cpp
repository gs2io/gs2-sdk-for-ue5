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

#include "Lottery/Domain/Model/Gs2LotteryEzUserGameSessionDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Lottery::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Lottery::Domain::Model::FEzLotteryGameSessionDomainPtr FEzUserGameSessionDomain::Lottery(
        const FString LotteryName
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Model::FEzLotteryGameSessionDomain>(
            Domain->Lottery(
                LotteryName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeBoxesIteratorPtr FEzUserGameSessionDomain::Boxes(
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeBoxesIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeBoxes(TFunction<void()> Callback)
    {
        return Domain->SubscribeBoxes(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeBoxes(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBoxes(
            CallbackId
        );
    }

    Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomainPtr FEzUserGameSessionDomain::BoxItems(
        const FString PrizeTableName
    ) const
    {
        return MakeShared<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>(
            Domain->BoxItems(
                PrizeTableName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
