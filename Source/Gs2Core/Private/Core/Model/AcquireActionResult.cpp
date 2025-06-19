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

#include "Core/Model/AcquireActionResult.h"

namespace Gs2::Core::Model
{
    FAcquireActionResult::FAcquireActionResult():
        ActionValue(TOptional<FString>()),
        AcquireRequestValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        AcquireResultValue(TOptional<FString>())
    {
    }

    FAcquireActionResult::FAcquireActionResult(
        const FAcquireActionResult& From
    ):
        ActionValue(From.ActionValue),
        AcquireRequestValue(From.AcquireRequestValue),
        StatusCodeValue(From.StatusCodeValue),
        AcquireResultValue(From.AcquireResultValue)
    {
    }

    TSharedPtr<FAcquireActionResult> FAcquireActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionResult> FAcquireActionResult::WithAcquireRequest(
        const TOptional<FString> AcquireRequest
    )
    {
        this->AcquireRequestValue = AcquireRequest;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionResult> FAcquireActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionResult> FAcquireActionResult::WithAcquireResult(
        const TOptional<FString> AcquireResult
    )
    {
        this->AcquireResultValue = AcquireResult;
        return SharedThis(this);
    }
    TOptional<FString> FAcquireActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FAcquireActionResult::GetAcquireRequest() const
    {
        return AcquireRequestValue;
    }
    TOptional<int32> FAcquireActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FAcquireActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FAcquireActionResult::GetAcquireResult() const
    {
        return AcquireResultValue;
    }

    TSharedPtr<FAcquireActionResult> FAcquireActionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionResult>()
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireRequest(Data->HasField(ANSI_TO_TCHAR("acquireRequest")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("acquireRequest"), v))
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
            ->WithAcquireResult(Data->HasField(ANSI_TO_TCHAR("acquireResult")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("acquireResult"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAcquireActionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
        }
        if (AcquireRequestValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireRequest", AcquireRequestValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (AcquireResultValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireResult", AcquireResultValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAcquireActionResult::TypeName = "AcquireActionResult";
}