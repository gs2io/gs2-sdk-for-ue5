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

#include "Distributor/Result/RunVerifyTaskResult.h"

namespace Gs2::Distributor::Result
{
    FRunVerifyTaskResult::FRunVerifyTaskResult():
        ContextStackValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>())
    {
    }

    FRunVerifyTaskResult::FRunVerifyTaskResult(
        const FRunVerifyTaskResult& From
    ):
        ContextStackValue(From.ContextStackValue),
        StatusCodeValue(From.StatusCodeValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FRunVerifyTaskResult> FRunVerifyTaskResult::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskResult> FRunVerifyTaskResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskResult> FRunVerifyTaskResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TOptional<FString> FRunVerifyTaskResult::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<int32> FRunVerifyTaskResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FRunVerifyTaskResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }

    TOptional<FString> FRunVerifyTaskResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FRunVerifyTaskResult> FRunVerifyTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunVerifyTaskResult>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contextStack"), v))
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
            ->WithResult(Data->HasField(ANSI_TO_TCHAR("result")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("result"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunVerifyTaskResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
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