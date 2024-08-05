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
#include "../Model/AccessLogWithTelemetry.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FQueryAccessLogWithTelemetryResult final : public TSharedFromThis<FQueryAccessLogWithTelemetryResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FAccessLogWithTelemetry>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        TOptional<int64> TotalCountValue;
        TOptional<int64> ScanSizeValue;
        
    public:
        
        FQueryAccessLogWithTelemetryResult();
        FQueryAccessLogWithTelemetryResult(
            const FQueryAccessLogWithTelemetryResult& From
        );
        ~FQueryAccessLogWithTelemetryResult() = default;

        TSharedPtr<FQueryAccessLogWithTelemetryResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FAccessLogWithTelemetry>>> Items);
        TSharedPtr<FQueryAccessLogWithTelemetryResult> WithNextPageToken(const TOptional<FString> NextPageToken);
        TSharedPtr<FQueryAccessLogWithTelemetryResult> WithTotalCount(const TOptional<int64> TotalCount);
        TSharedPtr<FQueryAccessLogWithTelemetryResult> WithScanSize(const TOptional<int64> ScanSize);

        TSharedPtr<TArray<TSharedPtr<Model::FAccessLogWithTelemetry>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;
        TOptional<int64> GetTotalCount() const;
        FString GetTotalCountString() const;
        TOptional<int64> GetScanSize() const;
        FString GetScanSizeString() const;

        static TSharedPtr<FQueryAccessLogWithTelemetryResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryAccessLogWithTelemetryResult, ESPMode::ThreadSafe> FQueryAccessLogWithTelemetryResultPtr;
}