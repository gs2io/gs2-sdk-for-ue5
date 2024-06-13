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

#include "Enchant/Domain/Model/Gs2EnchantEzUserGameSessionDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
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
        Gs2::Enchant::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterStatusesIteratorPtr FEzUserGameSessionDomain::BalanceParameterStatuses(
          const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterStatusesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeBalanceParameterStatuses(TFunction<void()> Callback)
    {
        return Domain->SubscribeBalanceParameterStatuses(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeBalanceParameterStatuses(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBalanceParameterStatuses(
            CallbackId
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomainPtr FEzUserGameSessionDomain::BalanceParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomain>(
            Domain->BalanceParameterStatus(
                ParameterName,
                PropertyId
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterStatusesIteratorPtr FEzUserGameSessionDomain::RarityParameterStatuses(
          const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterStatusesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeRarityParameterStatuses(TFunction<void()> Callback)
    {
        return Domain->SubscribeRarityParameterStatuses(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeRarityParameterStatuses(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRarityParameterStatuses(
            CallbackId
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomainPtr FEzUserGameSessionDomain::RarityParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomain>(
            Domain->RarityParameterStatus(
                ParameterName,
                PropertyId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
