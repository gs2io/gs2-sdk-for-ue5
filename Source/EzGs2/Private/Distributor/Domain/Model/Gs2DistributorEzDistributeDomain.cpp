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

#include "Distributor/Domain/Model/Gs2DistributorEzDistributeDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzDistributeDomain::InboxNamespaceId() const
    {
        return Domain->InboxNamespaceId;
    }

    TOptional<FString> FEzDistributeDomain::Result() const
    {
        return Domain->Result;
    }

    TOptional<FString> FEzDistributeDomain::ContextStack() const
    {
        return Domain->ContextStack;
    }

    TSharedPtr<TArray<FString>> FEzDistributeDomain::TaskResults() const
    {
        return Domain->TaskResults;
    }

    TOptional<FString> FEzDistributeDomain::SheetResult() const
    {
        return Domain->SheetResult;
    }

    TOptional<FString> FEzDistributeDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzDistributeDomain::FEzDistributeDomain(
        Gs2::Distributor::Domain::Model::FDistributeDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }
}
