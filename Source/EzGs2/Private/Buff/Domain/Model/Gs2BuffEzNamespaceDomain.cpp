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

#include "Buff/Domain/Model/Gs2BuffEzNamespaceDomain.h"

namespace Gs2::UE5::Buff::Domain::Model
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
        Gs2::Buff::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Buff::Domain::Iterator::FEzDescribeBuffEntryModelsIteratorPtr FEzNamespaceDomain::BuffEntryModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Buff::Domain::Iterator::FEzDescribeBuffEntryModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeBuffEntryModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeBuffEntryModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeBuffEntryModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeBuffEntryModels(
            CallbackId
        );
    }

    Gs2::UE5::Buff::Domain::Model::FEzBuffEntryModelDomainPtr FEzNamespaceDomain::BuffEntryModel(
        const FString BuffEntryName
    ) const
    {
        return MakeShared<Gs2::UE5::Buff::Domain::Model::FEzBuffEntryModelDomain>(
            Domain->BuffEntryModel(
                BuffEntryName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Buff::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Buff::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Buff::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::FGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Buff::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()->ToModel()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
