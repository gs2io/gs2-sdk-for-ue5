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
#include "../Model/LogEntry.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FQueryLogResult final : public TSharedFromThis<FQueryLogResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> ItemsValue;
        TOptional<int32> TotalEntryCountValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FQueryLogResult();
        FQueryLogResult(
            const FQueryLogResult& From
        );
        ~FQueryLogResult() = default;

        TSharedPtr<FQueryLogResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> Items);
        TSharedPtr<FQueryLogResult> WithTotalEntryCount(const TOptional<int32> TotalEntryCount);
        TSharedPtr<FQueryLogResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> GetItems() const;
        TOptional<int32> GetTotalEntryCount() const;
        FString GetTotalEntryCountString() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FQueryLogResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryLogResult, ESPMode::ThreadSafe> FQueryLogResultPtr;
}