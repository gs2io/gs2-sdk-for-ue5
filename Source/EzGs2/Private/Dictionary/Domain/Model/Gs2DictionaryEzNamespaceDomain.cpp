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

#include "Dictionary/Domain/Model/Gs2DictionaryEzNamespaceDomain.h"

namespace Gs2::UE5::Dictionary::Domain::Model
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
        Gs2::Dictionary::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntryModelsIteratorPtr FEzNamespaceDomain::EntryModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntryModelsIterator>(
            Domain->EntryModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeEntryModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeEntryModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeEntryModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeEntryModels(
            CallbackId
        );
    }

    Gs2::UE5::Dictionary::Domain::Model::FEzEntryModelDomainPtr FEzNamespaceDomain::EntryModel(
        const FString EntryName
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzEntryModelDomain>(
            Domain->EntryModel(
                EntryName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Dictionary::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Dictionary::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
