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

#include "Gateway/Domain/Model/Gs2GatewayEzUserDomain.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    TOptional<FString> FEzUserDomain::Protocol() const
    {
        return Domain->Protocol;
    }

    TSharedPtr<TArray<FString>> FEzUserDomain::SendConnectionIds() const
    {
        return Domain->SendConnectionIds;
    }

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Gateway::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionDomainPtr FEzUserDomain::WebSocketSession(
    ) const
    {
        return MakeShared<Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionDomain>(
            Domain->WebSocketSession(
            ),
            ConnectionValue
        );
    }
}
