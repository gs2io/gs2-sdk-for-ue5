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
#include "../Model/ExecuteStampSheetLogCount.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FCountExecuteStampSheetLogResult final : public TSharedFromThis<FCountExecuteStampSheetLogResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FExecuteStampSheetLogCount>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        TOptional<int64> TotalCountValue;
        TOptional<int64> ScanSizeValue;
        
    public:
        
        FCountExecuteStampSheetLogResult();
        FCountExecuteStampSheetLogResult(
            const FCountExecuteStampSheetLogResult& From
        );
        ~FCountExecuteStampSheetLogResult() = default;

        TSharedPtr<FCountExecuteStampSheetLogResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FExecuteStampSheetLogCount>>> Items);
        TSharedPtr<FCountExecuteStampSheetLogResult> WithNextPageToken(const TOptional<FString> NextPageToken);
        TSharedPtr<FCountExecuteStampSheetLogResult> WithTotalCount(const TOptional<int64> TotalCount);
        TSharedPtr<FCountExecuteStampSheetLogResult> WithScanSize(const TOptional<int64> ScanSize);

        TSharedPtr<TArray<TSharedPtr<Model::FExecuteStampSheetLogCount>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;
        TOptional<int64> GetTotalCount() const;
        FString GetTotalCountString() const;
        TOptional<int64> GetScanSize() const;
        FString GetScanSizeString() const;

        static TSharedPtr<FCountExecuteStampSheetLogResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountExecuteStampSheetLogResult, ESPMode::ThreadSafe> FCountExecuteStampSheetLogResultPtr;
}