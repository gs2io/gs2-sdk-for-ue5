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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzNamespaceDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzNamespaceDomain::UploadToken() const
    {
        return Domain->UploadToken;
    }

    TOptional<FString> FEzNamespaceDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::SerialKey::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::SerialKey::Domain::Model::FEzCampaignModelDomainPtr FEzNamespaceDomain::CampaignModel(
        const FString CampaignModelName
    ) const
    {
        return MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzCampaignModelDomain>(
            Domain->CampaignModel(
                CampaignModelName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::SerialKey::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::SerialKey::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
