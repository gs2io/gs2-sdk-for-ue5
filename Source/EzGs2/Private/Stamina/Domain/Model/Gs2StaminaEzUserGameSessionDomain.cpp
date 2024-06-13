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

#include "Stamina/Domain/Model/Gs2StaminaEzUserGameSessionDomain.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    TOptional<int32> FEzUserGameSessionDomain::OverflowValue() const
    {
        return Domain->OverflowValue;
    }

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
        Gs2::Stamina::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Stamina::Domain::Iterator::FEzDescribeStaminasIteratorPtr FEzUserGameSessionDomain::Staminas(
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Iterator::FEzDescribeStaminasIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeStaminas(TFunction<void()> Callback)
    {
        return Domain->SubscribeStaminas(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeStaminas(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeStaminas(
            CallbackId
        );
    }

    Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomainPtr FEzUserGameSessionDomain::Stamina(
        const FString StaminaName
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomain>(
            Domain->Stamina(
                StaminaName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
