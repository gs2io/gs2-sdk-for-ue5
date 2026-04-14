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
#include "../Model/Trace.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FGetTraceResult final : public TSharedFromThis<FGetTraceResult>
    {
        TSharedPtr<Model::FTrace> TraceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FTrace>>> ParallelsValue;
        TOptional<bool> ParallelTruncatedValue;
        
    public:
        
        FGetTraceResult();
        FGetTraceResult(
            const FGetTraceResult& From
        );
        ~FGetTraceResult() = default;

        TSharedPtr<FGetTraceResult> WithTrace(const TSharedPtr<Model::FTrace> Trace);
        TSharedPtr<FGetTraceResult> WithParallels(const TSharedPtr<TArray<TSharedPtr<Model::FTrace>>> Parallels);
        TSharedPtr<FGetTraceResult> WithParallelTruncated(const TOptional<bool> ParallelTruncated);

        TSharedPtr<Model::FTrace> GetTrace() const;
        TSharedPtr<TArray<TSharedPtr<Model::FTrace>>> GetParallels() const;
        TOptional<bool> GetParallelTruncated() const;
        FString GetParallelTruncatedString() const;

        static TSharedPtr<FGetTraceResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetTraceResult, ESPMode::ThreadSafe> FGetTraceResultPtr;
}