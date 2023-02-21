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

#include "Distributor/Domain/Model/Gs2DistributorEzNamespaceDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Result() const
    {
        return Domain->Result;
    }

    TOptional<FString> FEzNamespaceDomain::ContextStack() const
    {
        return Domain->ContextStack;
    }

    TSharedPtr<TArray<FString>> FEzNamespaceDomain::TaskResults() const
    {
        return Domain->TaskResults;
    }

    TOptional<FString> FEzNamespaceDomain::SheetResult() const
    {
        return Domain->SheetResult;
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
        Gs2::Distributor::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Distributor::Domain::Iterator::FEzDescribeDistributorModelsIteratorPtr FEzNamespaceDomain::DistributorModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Iterator::FEzDescribeDistributorModelsIterator>(
            Domain->DistributorModels(
            )
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzDistributorModelDomainPtr FEzNamespaceDomain::DistributorModel(
        const FString DistributorName
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzDistributorModelDomain>(
            Domain->DistributorModel(
                DistributorName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
