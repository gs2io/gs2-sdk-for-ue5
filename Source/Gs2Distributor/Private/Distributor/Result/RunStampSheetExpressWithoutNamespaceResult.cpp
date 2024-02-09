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

#include "Distributor/Result/RunStampSheetExpressWithoutNamespaceResult.h"

namespace Gs2::Distributor::Result
{
    FRunStampSheetExpressWithoutNamespaceResult::FRunStampSheetExpressWithoutNamespaceResult():
        TaskResultCodesValue(nullptr),
        TaskResultsValue(nullptr),
        SheetResultCodeValue(TOptional<int32>()),
        SheetResultValue(TOptional<FString>())
    {
    }

    FRunStampSheetExpressWithoutNamespaceResult::FRunStampSheetExpressWithoutNamespaceResult(
        const FRunStampSheetExpressWithoutNamespaceResult& From
    ):
        TaskResultCodesValue(From.TaskResultCodesValue),
        TaskResultsValue(From.TaskResultsValue),
        SheetResultCodeValue(From.SheetResultCodeValue),
        SheetResultValue(From.SheetResultValue)
    {
    }

    TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FRunStampSheetExpressWithoutNamespaceResult::WithTaskResultCodes(
        const TSharedPtr<TArray<int32>> TaskResultCodes
    )
    {
        this->TaskResultCodesValue = TaskResultCodes;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FRunStampSheetExpressWithoutNamespaceResult::WithTaskResults(
        const TSharedPtr<TArray<FString>> TaskResults
    )
    {
        this->TaskResultsValue = TaskResults;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FRunStampSheetExpressWithoutNamespaceResult::WithSheetResultCode(
        const TOptional<int32> SheetResultCode
    )
    {
        this->SheetResultCodeValue = SheetResultCode;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FRunStampSheetExpressWithoutNamespaceResult::WithSheetResult(
        const TOptional<FString> SheetResult
    )
    {
        this->SheetResultValue = SheetResult;
        return SharedThis(this);
    }

    TSharedPtr<TArray<int32>> FRunStampSheetExpressWithoutNamespaceResult::GetTaskResultCodes() const
    {
        if (!TaskResultCodesValue.IsValid())
        {
            return nullptr;
        }
        return TaskResultCodesValue;
    }

    TSharedPtr<TArray<FString>> FRunStampSheetExpressWithoutNamespaceResult::GetTaskResults() const
    {
        if (!TaskResultsValue.IsValid())
        {
            return nullptr;
        }
        return TaskResultsValue;
    }

    TOptional<int32> FRunStampSheetExpressWithoutNamespaceResult::GetSheetResultCode() const
    {
        return SheetResultCodeValue;
    }

    FString FRunStampSheetExpressWithoutNamespaceResult::GetSheetResultCodeString() const
    {
        if (!SheetResultCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SheetResultCodeValue.GetValue());
    }

    TOptional<FString> FRunStampSheetExpressWithoutNamespaceResult::GetSheetResult() const
    {
        return SheetResultValue;
    }

    TSharedPtr<FRunStampSheetExpressWithoutNamespaceResult> FRunStampSheetExpressWithoutNamespaceResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunStampSheetExpressWithoutNamespaceResult>()
            ->WithTaskResultCodes(Data->HasField("taskResultCodes") ? [Data]() -> TSharedPtr<TArray<int32>>
                 {
                    auto v = MakeShared<TArray<int32>>();
                    if (!Data->HasTypedField<EJson::Null>("taskResultCodes") && Data->HasTypedField<EJson::Array>("taskResultCodes"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("taskResultCodes"))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<int32>>())
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
                 }() : MakeShared<TArray<FString>>())
            ->WithSheetResultCode(Data->HasField("sheetResultCode") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("sheetResultCode", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithSheetResult(Data->HasField("sheetResult") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("sheetResult", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunStampSheetExpressWithoutNamespaceResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TaskResultCodesValue != nullptr && TaskResultCodesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskResultCodesValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("taskResultCodes", v);
        }
        if (TaskResultsValue != nullptr && TaskResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TaskResultsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("taskResults", v);
        }
        if (SheetResultCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("sheetResultCode", SheetResultCodeValue.GetValue());
        }
        if (SheetResultValue.IsSet())
        {
            JsonRootObject->SetStringField("sheetResult", SheetResultValue.GetValue());
        }
        return JsonRootObject;
    }
}