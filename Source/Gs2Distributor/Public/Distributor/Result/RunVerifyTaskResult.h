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

namespace Gs2::Distributor::Result
{
    class GS2DISTRIBUTOR_API FRunVerifyTaskResult final : public TSharedFromThis<FRunVerifyTaskResult>
    {
        TOptional<FString> ContextStackValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultValue;
        
    public:
        
        FRunVerifyTaskResult();
        FRunVerifyTaskResult(
            const FRunVerifyTaskResult& From
        );
        ~FRunVerifyTaskResult() = default;

        TSharedPtr<FRunVerifyTaskResult> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRunVerifyTaskResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FRunVerifyTaskResult> WithResult(const TOptional<FString> Result);

        TOptional<FString> GetContextStack() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetResult() const;

        static TSharedPtr<FRunVerifyTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunVerifyTaskResult, ESPMode::ThreadSafe> FRunVerifyTaskResultPtr;
}