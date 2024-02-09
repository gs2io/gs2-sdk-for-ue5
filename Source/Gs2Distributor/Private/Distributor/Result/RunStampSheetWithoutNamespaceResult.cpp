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

#include "Distributor/Result/RunStampSheetWithoutNamespaceResult.h"

namespace Gs2::Distributor::Result
{
    FRunStampSheetWithoutNamespaceResult::FRunStampSheetWithoutNamespaceResult():
        StatusCodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>())
    {
    }

    FRunStampSheetWithoutNamespaceResult::FRunStampSheetWithoutNamespaceResult(
        const FRunStampSheetWithoutNamespaceResult& From
    ):
        StatusCodeValue(From.StatusCodeValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FRunStampSheetWithoutNamespaceResult> FRunStampSheetWithoutNamespaceResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampSheetWithoutNamespaceResult> FRunStampSheetWithoutNamespaceResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TOptional<int32> FRunStampSheetWithoutNamespaceResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FRunStampSheetWithoutNamespaceResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }

    TOptional<FString> FRunStampSheetWithoutNamespaceResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FRunStampSheetWithoutNamespaceResult> FRunStampSheetWithoutNamespaceResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunStampSheetWithoutNamespaceResult>()
            ->WithStatusCode(Data->HasField("statusCode") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("statusCode", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResult(Data->HasField("result") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("result", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunStampSheetWithoutNamespaceResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        return JsonRootObject;
    }
}