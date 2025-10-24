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

#include "Formation/Domain/Model/Gs2FormationEzNamespaceDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
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
        Gs2::Formation::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldModelsIteratorPtr FEzNamespaceDomain::MoldModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeMoldModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeMoldModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeMoldModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMoldModels(
            CallbackId
        );
    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormModelsIteratorPtr FEzNamespaceDomain::PropertyFormModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribePropertyFormModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribePropertyFormModels(TFunction<void()> Callback)
    {
        return Domain->SubscribePropertyFormModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribePropertyFormModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribePropertyFormModels(
            CallbackId
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomainPtr FEzNamespaceDomain::MoldModel(
        const FString MoldModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomain>(
            Domain->MoldModel(
                MoldModelName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzPropertyFormModelDomainPtr FEzNamespaceDomain::PropertyFormModel(
        const FString PropertyFormModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzPropertyFormModelDomain>(
            Domain->PropertyFormModel(
                PropertyFormModelName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
