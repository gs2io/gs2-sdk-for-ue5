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
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldModelsIteratorPtr FEzNamespaceDomain::MoldModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeMoldModelsIterator>(
            Domain->MoldModels(
            )
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomainPtr FEzNamespaceDomain::MoldModel(
        const FString MoldName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzMoldModelDomain>(
            Domain->MoldModel(
                MoldName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormModelsIteratorPtr FEzNamespaceDomain::FormModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormModelsIterator>(
            Domain->FormModels(
            )
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzFormModelDomainPtr FEzNamespaceDomain::FormModel(
        const FString FormModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormModelDomain>(
            Domain->FormModel(
                FormModelName
            ),
            ProfileValue
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
            ProfileValue
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
