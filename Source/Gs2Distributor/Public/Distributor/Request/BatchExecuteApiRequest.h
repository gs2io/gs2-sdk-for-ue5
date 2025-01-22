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
#include "Dom/JsonObject.h"
#include "../Model/BatchRequestPayload.h"

namespace Gs2::Distributor::Request
{
    class FBatchExecuteApiRequest;

    class GS2DISTRIBUTOR_API FBatchExecuteApiRequest final : public TSharedFromThis<FBatchExecuteApiRequest>
    {
        TOptional<FString> ContextStackValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBatchRequestPayload>>> RequestPayloadsValue;
        
    public:
        
        FBatchExecuteApiRequest();
        FBatchExecuteApiRequest(
            const FBatchExecuteApiRequest& From
        );
        ~FBatchExecuteApiRequest() = default;

        TSharedPtr<FBatchExecuteApiRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchExecuteApiRequest> WithRequestPayloads(const TSharedPtr<TArray<TSharedPtr<Model::FBatchRequestPayload>>> RequestPayloads);

        TOptional<FString> GetContextStack() const;TSharedPtr<TArray<TSharedPtr<Model::FBatchRequestPayload>>> GetRequestPayloads() const;

        static TSharedPtr<FBatchExecuteApiRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchExecuteApiRequest> FBatchExecuteApiRequestPtr;
}