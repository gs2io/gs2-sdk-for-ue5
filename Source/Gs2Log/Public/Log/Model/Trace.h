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
#include "Core/Gs2Object.h"
#include "LogEntry.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FTrace final : public FGs2Object, public TSharedFromThis<FTrace>
    {
        TOptional<FString> TraceIdValue;
        TSharedPtr<TArray<TSharedPtr<FLogEntry>>> SpansValue;
        TOptional<bool> TruncatedValue;

    public:
        FTrace();
        FTrace(
            const FTrace& From
        );
        virtual ~FTrace() override = default;

        TSharedPtr<FTrace> WithTraceId(const TOptional<FString> TraceId);
        TSharedPtr<FTrace> WithSpans(const TSharedPtr<TArray<TSharedPtr<FLogEntry>>> Spans);
        TSharedPtr<FTrace> WithTruncated(const TOptional<bool> Truncated);

        TOptional<FString> GetTraceId() const;
        TSharedPtr<TArray<TSharedPtr<FLogEntry>>> GetSpans() const;
        TOptional<bool> GetTruncated() const;
        FString GetTruncatedString() const;


        static TSharedPtr<FTrace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTrace, ESPMode::ThreadSafe> FTracePtr;
}