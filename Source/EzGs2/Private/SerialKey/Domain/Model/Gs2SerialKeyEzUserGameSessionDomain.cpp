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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzUserGameSessionDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::Url() const
    {
        return Domain->Url;
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
        Gs2::SerialKey::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyGameSessionDomainPtr FEzUserGameSessionDomain::SerialKey(
        const FString Code
    ) const
    {
        return MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyGameSessionDomain>(
            Domain->SerialKey(
                Code
            ),
            ProfileValue
        );
    }
}
