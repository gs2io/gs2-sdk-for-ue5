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

#include "Distributor/Result/RunStampSheetExpressResult.h"

namespace Gs2::Distributor::Result
{
    FRunStampSheetExpressResult::FRunStampSheetExpressResult():
        TaskResultsValue(nullptr),
        SheetResultValue(TOptional<FString>())
    {
    }

    FRunStampSheetExpressResult::FRunStampSheetExpressResult(
        const FRunStampSheetExpressResult& From
    ):
        TaskResultsValue(From.TaskResultsValue),
        SheetResultValue(From.SheetResultValue)
    {
    }

    TSharedPtr<FRunStampSheetExpressResult> FRunStampSheetExpressResult::WithTaskResults(
        const TSharedPtr<TArray<FString>> TaskResults
    )
    {
        this->TaskResultsValue = TaskResults;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampSheetExpressResult> FRunStampSheetExpressResult::WithSheetResult(
        const TOptional<FString> SheetResult
    )
    {
        this->SheetResultValue = SheetResult;
        return SharedThis(this);
    }

    TSharedPtr<TArray<FString>> FRunStampSheetExpressResult::GetTaskResults() const
    {
        if (!TaskResultsValue.IsValid())
        {
            return nullptr;
        }
        return TaskResultsValue;
    }

    TOptional<FString> FRunStampSheetExpressResult::GetSheetResult() const
    {
        return SheetResultValue;
    }

    TSharedPtr<FRunStampSheetExpressResult> FRunStampSheetExpressResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunStampSheetExpressResult>()
            ->WithTaskResults(Data->HasField("taskResults") ? [Data]() -> TSharedPtr<TArray<FString>>
                 {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("taskResults") && Data->HasTypedField<EJson::Array>("taskResults"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("taskResults"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithSheetResult(Data->HasField("sheetResult") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("sheetResult", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunStampSheetExpressResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TaskResultsValue != nullptr && TaskResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskResultsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("taskResults", v);
        }
        if (SheetResultValue.IsSet())
        {
            JsonRootObject->SetStringField("sheetResult", SheetResultValue.GetValue());
        }
        return JsonRootObject;
    }
}