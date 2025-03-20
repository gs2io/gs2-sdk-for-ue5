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

namespace Gs2::Log::Model
{
    class GS2LOG_API FAccessLogWithTelemetry final : public FGs2Object, public TSharedFromThis<FAccessLogWithTelemetry>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> SourceRequestIdValue;
        TOptional<FString> RequestIdValue;
        TOptional<int64> DurationValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RequestValue;
        TOptional<FString> ResultValue;
        TOptional<FString> StatusValue;

    public:
        FAccessLogWithTelemetry();
        FAccessLogWithTelemetry(
            const FAccessLogWithTelemetry& From
        );
        virtual ~FAccessLogWithTelemetry() override = default;

        TSharedPtr<FAccessLogWithTelemetry> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FAccessLogWithTelemetry> WithSourceRequestId(const TOptional<FString> SourceRequestId);
        TSharedPtr<FAccessLogWithTelemetry> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FAccessLogWithTelemetry> WithDuration(const TOptional<int64> Duration);
        TSharedPtr<FAccessLogWithTelemetry> WithService(const TOptional<FString> Service);
        TSharedPtr<FAccessLogWithTelemetry> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FAccessLogWithTelemetry> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAccessLogWithTelemetry> WithRequest(const TOptional<FString> Request);
        TSharedPtr<FAccessLogWithTelemetry> WithResult(const TOptional<FString> Result);
        TSharedPtr<FAccessLogWithTelemetry> WithStatus(const TOptional<FString> Status);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetSourceRequestId() const;
        TOptional<FString> GetRequestId() const;
        TOptional<int64> GetDuration() const;
        FString GetDurationString() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRequest() const;
        TOptional<FString> GetResult() const;
        TOptional<FString> GetStatus() const;


        static TSharedPtr<FAccessLogWithTelemetry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccessLogWithTelemetry, ESPMode::ThreadSafe> FAccessLogWithTelemetryPtr;
}