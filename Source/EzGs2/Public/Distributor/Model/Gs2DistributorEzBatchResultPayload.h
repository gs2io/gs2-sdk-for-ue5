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
#include "Distributor/Model/BatchResultPayload.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzBatchResultPayload final : public TSharedFromThis<FEzBatchResultPayload>
	{
        TOptional<FString> RequestIdValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultPayloadValue;

	public:
        TSharedPtr<FEzBatchResultPayload> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FEzBatchResultPayload> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzBatchResultPayload> WithResultPayload(const TOptional<FString> ResultPayload);

        TOptional<FString> GetRequestId() const;

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetResultPayload() const;

        Gs2::Distributor::Model::FBatchResultPayloadPtr ToModel() const;
        static TSharedPtr<FEzBatchResultPayload> FromModel(Gs2::Distributor::Model::FBatchResultPayloadPtr Model);
    };
    typedef TSharedPtr<FEzBatchResultPayload> FEzBatchResultPayloadPtr;
}