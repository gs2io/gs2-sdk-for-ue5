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

#include "Ranking/Result/CalcRankingResult.h"

namespace Gs2::Ranking::Result
{
    FCalcRankingResult::FCalcRankingResult():
        ProcessingValue(TOptional<bool>())
    {
    }

    FCalcRankingResult::FCalcRankingResult(
        const FCalcRankingResult& From
    ):
        ProcessingValue(From.ProcessingValue)
    {
    }

    TSharedPtr<FCalcRankingResult> FCalcRankingResult::WithProcessing(
        const TOptional<bool> Processing
    )
    {
        this->ProcessingValue = Processing;
        return SharedThis(this);
    }

    TOptional<bool> FCalcRankingResult::GetProcessing() const
    {
        return ProcessingValue;
    }

    FString FCalcRankingResult::GetProcessingString() const
    {
        if (!ProcessingValue.IsSet())
        {
            return FString("null");
        }
        return FString(ProcessingValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FCalcRankingResult> FCalcRankingResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCalcRankingResult>()
            ->WithProcessing(Data->HasField(ANSI_TO_TCHAR("processing")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("processing"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FCalcRankingResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProcessingValue.IsSet())
        {
            JsonRootObject->SetBoolField("processing", ProcessingValue.GetValue());
        }
        return JsonRootObject;
    }
}