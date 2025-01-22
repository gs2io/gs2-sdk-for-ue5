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

#include "Showcase/Model/ConsumeActionResult.h"

namespace Gs2::Showcase::Model
{
    FConsumeActionResult::FConsumeActionResult():
        ActionValue(TOptional<FString>()),
        ConsumeRequestValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        ConsumeResultValue(TOptional<FString>())
    {
    }

    FConsumeActionResult::FConsumeActionResult(
        const FConsumeActionResult& From
    ):
        ActionValue(From.ActionValue),
        ConsumeRequestValue(From.ConsumeRequestValue),
        StatusCodeValue(From.StatusCodeValue),
        ConsumeResultValue(From.ConsumeResultValue)
    {
    }

    TSharedPtr<FConsumeActionResult> FConsumeActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeActionResult> FConsumeActionResult::WithConsumeRequest(
        const TOptional<FString> ConsumeRequest
    )
    {
        this->ConsumeRequestValue = ConsumeRequest;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeActionResult> FConsumeActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeActionResult> FConsumeActionResult::WithConsumeResult(
        const TOptional<FString> ConsumeResult
    )
    {
        this->ConsumeResultValue = ConsumeResult;
        return SharedThis(this);
    }
    TOptional<FString> FConsumeActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FConsumeActionResult::GetConsumeRequest() const
    {
        return ConsumeRequestValue;
    }
    TOptional<int32> FConsumeActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FConsumeActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FConsumeActionResult::GetConsumeResult() const
    {
        return ConsumeResultValue;
    }

    TSharedPtr<FConsumeActionResult> FConsumeActionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConsumeActionResult>()
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithConsumeRequest(Data->HasField(ANSI_TO_TCHAR("consumeRequest")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("consumeRequest"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStatusCode(Data->HasField(ANSI_TO_TCHAR("statusCode")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("statusCode"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithConsumeResult(Data->HasField(ANSI_TO_TCHAR("consumeResult")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("consumeResult"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FConsumeActionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
        }
        if (ConsumeRequestValue.IsSet())
        {
            JsonRootObject->SetStringField("consumeRequest", ConsumeRequestValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (ConsumeResultValue.IsSet())
        {
            JsonRootObject->SetStringField("consumeResult", ConsumeResultValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FConsumeActionResult::TypeName = "ConsumeActionResult";
}