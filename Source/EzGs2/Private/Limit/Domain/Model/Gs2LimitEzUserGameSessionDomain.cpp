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

#include "Limit/Domain/Model/Gs2LimitEzUserGameSessionDomain.h"

namespace Gs2::UE5::Limit::Domain::Model
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
        Gs2::Limit::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Limit::Domain::Iterator::FEzDescribeCountersIteratorPtr FEzUserGameSessionDomain::Counters(
          const TOptional<FString> LimitName
    ) const
    {
        return MakeShared<Gs2::UE5::Limit::Domain::Iterator::FEzDescribeCountersIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            LimitName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeCounters(TFunction<void()> Callback)
    {
        return Domain->SubscribeCounters(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeCounters(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeCounters(
            CallbackId
        );
    }

    Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomainPtr FEzUserGameSessionDomain::Counter(
        const FString LimitName,
        const FString CounterName
    ) const
    {
        return MakeShared<Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomain>(
            Domain->Counter(
                LimitName,
                CounterName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
