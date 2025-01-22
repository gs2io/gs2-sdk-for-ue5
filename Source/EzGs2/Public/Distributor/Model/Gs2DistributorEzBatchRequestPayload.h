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

#pragma once

#include "CoreMinimal.h"
#include "Distributor/Model/BatchRequestPayload.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzBatchRequestPayload final : public TSharedFromThis<FEzBatchRequestPayload>
	{
        TOptional<FString> RequestIdValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodNameValue;
        TOptional<FString> ParameterValue;

	public:
        TSharedPtr<FEzBatchRequestPayload> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FEzBatchRequestPayload> WithService(const TOptional<FString> Service);
        TSharedPtr<FEzBatchRequestPayload> WithMethodName(const TOptional<FString> MethodName);
        TSharedPtr<FEzBatchRequestPayload> WithParameter(const TOptional<FString> Parameter);

        TOptional<FString> GetRequestId() const;

        TOptional<FString> GetService() const;

        TOptional<FString> GetMethodName() const;

        TOptional<FString> GetParameter() const;

        Gs2::Distributor::Model::FBatchRequestPayloadPtr ToModel() const;
        static TSharedPtr<FEzBatchRequestPayload> FromModel(Gs2::Distributor::Model::FBatchRequestPayloadPtr Model);
    };
    typedef TSharedPtr<FEzBatchRequestPayload> FEzBatchRequestPayloadPtr;
}