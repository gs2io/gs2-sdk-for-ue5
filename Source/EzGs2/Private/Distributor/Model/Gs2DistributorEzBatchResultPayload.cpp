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

#include "Distributor/Model/Gs2DistributorEzBatchResultPayload.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzBatchResultPayload> FEzBatchResultPayload::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBatchResultPayload> FEzBatchResultPayload::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzBatchResultPayload> FEzBatchResultPayload::WithResultPayload(
        const TOptional<FString> ResultPayload
    )
    {
        this->ResultPayloadValue = ResultPayload;
        return SharedThis(this);
    }
    TOptional<FString> FEzBatchResultPayload::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<int32> FEzBatchResultPayload::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzBatchResultPayload::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzBatchResultPayload::GetResultPayload() const
    {
        return ResultPayloadValue;
    }

    Gs2::Distributor::Model::FBatchResultPayloadPtr FEzBatchResultPayload::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FBatchResultPayload>()
            ->WithRequestId(RequestIdValue)
            ->WithStatusCode(StatusCodeValue)
            ->WithResultPayload(ResultPayloadValue);
    }

    TSharedPtr<FEzBatchResultPayload> FEzBatchResultPayload::FromModel(const Gs2::Distributor::Model::FBatchResultPayloadPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBatchResultPayload>()
            ->WithRequestId(Model->GetRequestId())
            ->WithStatusCode(Model->GetStatusCode())
            ->WithResultPayload(Model->GetResultPayload());
    }
}