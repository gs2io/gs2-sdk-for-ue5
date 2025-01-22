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

    TOptional<int32> FEzDistributeDomain::StatusCode() const
    {
        return Domain->StatusCode;
    }

    TSharedPtr<TArray<int32>> FEzDistributeDomain::VerifyTaskResultCodes() const
    {
        return Domain->VerifyTaskResultCodes;
    }

    TSharedPtr<TArray<FString>> FEzDistributeDomain::VerifyTaskResults() const
    {
        return Domain->VerifyTaskResults;
    }

    TSharedPtr<TArray<int32>> FEzDistributeDomain::TaskResultCodes() const
    {
        return Domain->TaskResultCodes;
    }

    TSharedPtr<TArray<FString>> FEzDistributeDomain::TaskResults() const
    {
        return Domain->TaskResults;
    }

    TOptional<int32> FEzDistributeDomain::SheetResultCode() const
    {
        return Domain->SheetResultCode;
    }

    TOptional<FString> FEzDistributeDomain::SheetResult() const
    {
        return Domain->SheetResult;
    }

    TOptional<FString> FEzDistributeDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzDistributeDomain::Signature() const
    {
        return Domain->Signature;
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchResultPayload>>> FEzDistributeDomain::Results() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchResultPayload>>>();
            for (auto Value : *Domain->Results) {
                Result->Add(
                    Gs2::UE5::Distributor::Model::FEzBatchResultPayload::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
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
