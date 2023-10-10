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

#include "Version/Domain/Model/Gs2VersionEzNamespaceDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Url() const
    {
        return Domain->Url;
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
        Gs2::Version::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Version::Domain::Iterator::FEzDescribeVersionModelsIteratorPtr FEzNamespaceDomain::VersionModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Iterator::FEzDescribeVersionModelsIterator>(
            Domain->VersionModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeVersionModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeVersionModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeVersionModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeVersionModels(
            CallbackId
        );
    }

    Gs2::UE5::Version::Domain::Model::FEzVersionModelDomainPtr FEzNamespaceDomain::VersionModel(
        const FString VersionName
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzVersionModelDomain>(
            Domain->VersionModel(
                VersionName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Version::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Version::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
