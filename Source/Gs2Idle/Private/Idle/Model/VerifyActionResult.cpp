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

#include "Idle/Model/VerifyActionResult.h"

namespace Gs2::Idle::Model
{
    FVerifyActionResult::FVerifyActionResult():
        ActionValue(TOptional<FString>()),
        VerifyRequestValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        VerifyResultValue(TOptional<FString>())
    {
    }

    FVerifyActionResult::FVerifyActionResult(
        const FVerifyActionResult& From
    ):
        ActionValue(From.ActionValue),
        VerifyRequestValue(From.VerifyRequestValue),
        StatusCodeValue(From.StatusCodeValue),
        VerifyResultValue(From.VerifyResultValue)
    {
    }

    TSharedPtr<FVerifyActionResult> FVerifyActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyActionResult> FVerifyActionResult::WithVerifyRequest(
        const TOptional<FString> VerifyRequest
    )
    {
        this->VerifyRequestValue = VerifyRequest;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyActionResult> FVerifyActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyActionResult> FVerifyActionResult::WithVerifyResult(
        const TOptional<FString> VerifyResult
    )
    {
        this->VerifyResultValue = VerifyResult;
        return SharedThis(this);
    }
    TOptional<FString> FVerifyActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FVerifyActionResult::GetVerifyRequest() const
    {
        return VerifyRequestValue;
    }
    TOptional<int32> FVerifyActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FVerifyActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FVerifyActionResult::GetVerifyResult() const
    {
        return VerifyResultValue;
    }

    TSharedPtr<FVerifyActionResult> FVerifyActionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyActionResult>()
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVerifyRequest(Data->HasField(ANSI_TO_TCHAR("verifyRequest")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyRequest"), v))
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
            ->WithVerifyResult(Data->HasField(ANSI_TO_TCHAR("verifyResult")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyResult"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyActionResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
        }
        if (VerifyRequestValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyRequest", VerifyRequestValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (VerifyResultValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyResult", VerifyResultValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FVerifyActionResult::TypeName = "VerifyActionResult";
}