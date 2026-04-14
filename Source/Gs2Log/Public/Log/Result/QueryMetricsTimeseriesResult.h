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
#include "../Model/TimeseriesPoint.h"
#include "../Model/TimeseriesMetadata.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FQueryMetricsTimeseriesResult final : public TSharedFromThis<FQueryMetricsTimeseriesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesPoint>>> ItemsValue;
        TSharedPtr<Model::FTimeseriesMetadata> TimeseriesMetadataValue;
        
    public:
        
        FQueryMetricsTimeseriesResult();
        FQueryMetricsTimeseriesResult(
            const FQueryMetricsTimeseriesResult& From
        );
        ~FQueryMetricsTimeseriesResult() = default;

        TSharedPtr<FQueryMetricsTimeseriesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesPoint>>> Items);
        TSharedPtr<FQueryMetricsTimeseriesResult> WithTimeseriesMetadata(const TSharedPtr<Model::FTimeseriesMetadata> TimeseriesMetadata);

        TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesPoint>>> GetItems() const;
        TSharedPtr<Model::FTimeseriesMetadata> GetTimeseriesMetadata() const;

        static TSharedPtr<FQueryMetricsTimeseriesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryMetricsTimeseriesResult, ESPMode::ThreadSafe> FQueryMetricsTimeseriesResultPtr;
}