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

#include "Enchant/Domain/Model/Gs2EnchantEzNamespaceDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
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
        Gs2::Enchant::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterModelsIteratorPtr FEzNamespaceDomain::BalanceParameterModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeBalanceParameterModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeBalanceParameterModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeBalanceParameterModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeBalanceParameterModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBalanceParameterModels(
            CallbackId
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterModelDomainPtr FEzNamespaceDomain::BalanceParameterModel(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterModelDomain>(
            Domain->BalanceParameterModel(
                ParameterName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterModelsIteratorPtr FEzNamespaceDomain::RarityParameterModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Iterator::FEzDescribeRarityParameterModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeRarityParameterModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeRarityParameterModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeRarityParameterModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRarityParameterModels(
            CallbackId
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterModelDomainPtr FEzNamespaceDomain::RarityParameterModel(
        const FString ParameterName
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterModelDomain>(
            Domain->RarityParameterModel(
                ParameterName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Enchant::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Enchant::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
