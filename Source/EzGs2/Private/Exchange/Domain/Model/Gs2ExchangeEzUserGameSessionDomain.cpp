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

#include "Exchange/Domain/Model/Gs2ExchangeEzUserGameSessionDomain.h"

namespace Gs2::UE5::Exchange::Domain::Model
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
        Gs2::Exchange::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomainPtr FEzUserGameSessionDomain::Exchange(
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>(
            Domain->Exchange(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeAwaitsIteratorPtr FEzUserGameSessionDomain::Awaits(
          const TOptional<FString> RateName
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeAwaitsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RateName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeAwaits(TFunction<void()> Callback)
    {
        return Domain->SubscribeAwaits(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeAwaits(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeAwaits(
            CallbackId
        );
    }

    Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomainPtr FEzUserGameSessionDomain::Await(
        const FString AwaitName
    ) const
    {
        return MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>(
            Domain->Await(
                AwaitName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
