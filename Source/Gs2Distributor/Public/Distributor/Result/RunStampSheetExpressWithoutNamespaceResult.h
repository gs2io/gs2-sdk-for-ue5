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
    class GS2DISTRIBUTOR_API FRunStampSheetExpressWithoutNamespaceResult final : public TSharedFromThis<FRunStampSheetExpressWithoutNamespaceResult>
    {
        TSharedPtr<TArray<FString>> TaskResultsValue;
        TOptional<FString> SheetResultValue;
        
    public:
        
        FRunStampSheetExpressWithoutNamespaceResult();
        FRunStampSheetExpressWithoutNamespaceResult(
            const FRunStampSheetExpressWithoutNamespaceResult& From
        );
        ~FRunStampSheetExpressWithoutNamespaceResult() = default;

        TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> WithTaskResults(const TSharedPtr<TArray<FString>> TaskResults);
        TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> WithSheetResult(const TOptional<FString> SheetResult);

        TSharedPtr<TArray<FString>> GetTaskResults() const;
        TOptional<FString> GetSheetResult() const;

        static TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult, ESPMode::ThreadSafe> FRunStampSheetExpressWithoutNamespaceResultPtr;
}