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

#include "Distributor/Model/Gs2DistributorEzBatchRequestPayload.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayload::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayload::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayload::WithMethodName(
        const TOptional<FString> MethodName
    )
    {
        this->MethodNameValue = MethodName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayload::WithParameter(
        const TOptional<FString> Parameter
    )
    {
        this->ParameterValue = Parameter;
        return SharedThis(this);
    }
    TOptional<FString> FEzBatchRequestPayload::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<FString> FEzBatchRequestPayload::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FEzBatchRequestPayload::GetMethodName() const
    {
        return MethodNameValue;
    }
    TOptional<FString> FEzBatchRequestPayload::GetParameter() const
    {
        return ParameterValue;
    }

    Gs2::Distributor::Model::FBatchRequestPayloadPtr FEzBatchRequestPayload::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FBatchRequestPayload>()
            ->WithRequestId(RequestIdValue)
            ->WithService(ServiceValue)
            ->WithMethodName(MethodNameValue)
            ->WithParameter(ParameterValue);
    }

    TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayload::FromModel(const Gs2::Distributor::Model::FBatchRequestPayloadPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBatchRequestPayload>()
            ->WithRequestId(Model->GetRequestId())
            ->WithService(Model->GetService())
            ->WithMethodName(Model->GetMethodName())
            ->WithParameter(Model->GetParameter());
    }
}