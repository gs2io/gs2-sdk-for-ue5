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
#include "../Model/RandomStatus.h"

namespace Gs2::Script::Result
{
    class GS2SCRIPT_API FDebugInvokeResult final : public TSharedFromThis<FDebugInvokeResult>
    {
        TOptional<int32> CodeValue;
        TOptional<FString> ResultValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Model::FRandomStatus> RandomStatusValue;
        TOptional<int32> ExecuteTimeValue;
        TOptional<int32> ChargedValue;
        TSharedPtr<TArray<FString>> OutputValue;
        
    public:
        
        FDebugInvokeResult();
        FDebugInvokeResult(
            const FDebugInvokeResult& From
        );
        ~FDebugInvokeResult() = default;

        TSharedPtr<FDebugInvokeResult> WithCode(const TOptional<int32> Code);
        TSharedPtr<FDebugInvokeResult> WithResult(const TOptional<FString> Result);
        TSharedPtr<FDebugInvokeResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FDebugInvokeResult> WithRandomStatus(const TSharedPtr<Model::FRandomStatus> RandomStatus);
        TSharedPtr<FDebugInvokeResult> WithExecuteTime(const TOptional<int32> ExecuteTime);
        TSharedPtr<FDebugInvokeResult> WithCharged(const TOptional<int32> Charged);
        TSharedPtr<FDebugInvokeResult> WithOutput(const TSharedPtr<TArray<FString>> Output);

        TOptional<int32> GetCode() const;
        FString GetCodeString() const;
        TOptional<FString> GetResult() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Model::FRandomStatus> GetRandomStatus() const;
        TOptional<int32> GetExecuteTime() const;
        FString GetExecuteTimeString() const;
        TOptional<int32> GetCharged() const;
        FString GetChargedString() const;
        TSharedPtr<TArray<FString>> GetOutput() const;

        static TSharedPtr<FDebugInvokeResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDebugInvokeResult, ESPMode::ThreadSafe> FDebugInvokeResultPtr;
}