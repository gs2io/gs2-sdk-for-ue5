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

#include "Stamina/Domain/Model/Gs2StaminaEzNamespaceDomain.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
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
        Gs2::Stamina::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Stamina::Domain::Iterator::FEzDescribeStaminaModelsIteratorPtr FEzNamespaceDomain::StaminaModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Iterator::FEzDescribeStaminaModelsIterator>(
            Domain->StaminaModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeStaminaModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeStaminaModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeStaminaModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeStaminaModels(
            CallbackId
        );
    }

    Gs2::UE5::Stamina::Domain::Model::FEzStaminaModelDomainPtr FEzNamespaceDomain::StaminaModel(
        const FString StaminaName
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzStaminaModelDomain>(
            Domain->StaminaModel(
                StaminaName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Stamina::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Stamina::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Stamina::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
