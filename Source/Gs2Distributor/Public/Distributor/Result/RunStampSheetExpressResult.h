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
    class GS2DISTRIBUTOR_API FRunStampSheetExpressResult final : public TSharedFromThis<FRunStampSheetExpressResult>
    {
        TSharedPtr<TArray<int32>> VerifyTaskResultCodesValue;
        TSharedPtr<TArray<FString>> VerifyTaskResultsValue;
        TSharedPtr<TArray<int32>> TaskResultCodesValue;
        TSharedPtr<TArray<FString>> TaskResultsValue;
        TOptional<int32> SheetResultCodeValue;
        TOptional<FString> SheetResultValue;
        
    public:
        
        FRunStampSheetExpressResult();
        FRunStampSheetExpressResult(
            const FRunStampSheetExpressResult& From
        );
        ~FRunStampSheetExpressResult() = default;

        TSharedPtr<FRunStampSheetExpressResult> WithVerifyTaskResultCodes(const TSharedPtr<TArray<int32>> VerifyTaskResultCodes);
        TSharedPtr<FRunStampSheetExpressResult> WithVerifyTaskResults(const TSharedPtr<TArray<FString>> VerifyTaskResults);
        TSharedPtr<FRunStampSheetExpressResult> WithTaskResultCodes(const TSharedPtr<TArray<int32>> TaskResultCodes);
        TSharedPtr<FRunStampSheetExpressResult> WithTaskResults(const TSharedPtr<TArray<FString>> TaskResults);
        TSharedPtr<FRunStampSheetExpressResult> WithSheetResultCode(const TOptional<int32> SheetResultCode);
        TSharedPtr<FRunStampSheetExpressResult> WithSheetResult(const TOptional<FString> SheetResult);

        TSharedPtr<TArray<int32>> GetVerifyTaskResultCodes() const;
        TSharedPtr<TArray<FString>> GetVerifyTaskResults() const;
        TSharedPtr<TArray<int32>> GetTaskResultCodes() const;
        TSharedPtr<TArray<FString>> GetTaskResults() const;
        TOptional<int32> GetSheetResultCode() const;
        FString GetSheetResultCodeString() const;
        TOptional<FString> GetSheetResult() const;

        static TSharedPtr<FRunStampSheetExpressResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunStampSheetExpressResult, ESPMode::ThreadSafe> FRunStampSheetExpressResultPtr;
}