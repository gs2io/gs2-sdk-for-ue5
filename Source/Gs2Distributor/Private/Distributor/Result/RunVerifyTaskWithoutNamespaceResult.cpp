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

#include "Distributor/Result/RunVerifyTaskWithoutNamespaceResult.h"

namespace Gs2::Distributor::Result
{
    FRunVerifyTaskWithoutNamespaceResult::FRunVerifyTaskWithoutNamespaceResult():
        ContextStackValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>())
    {
    }

    FRunVerifyTaskWithoutNamespaceResult::FRunVerifyTaskWithoutNamespaceResult(
        const FRunVerifyTaskWithoutNamespaceResult& From
    ):
        ContextStackValue(From.ContextStackValue),
        StatusCodeValue(From.StatusCodeValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceResult> FRunVerifyTaskWithoutNamespaceResult::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceResult> FRunVerifyTaskWithoutNamespaceResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceResult> FRunVerifyTaskWithoutNamespaceResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TOptional<FString> FRunVerifyTaskWithoutNamespaceResult::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<int32> FRunVerifyTaskWithoutNamespaceResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FRunVerifyTaskWithoutNamespaceResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }

    TOptional<FString> FRunVerifyTaskWithoutNamespaceResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceResult> FRunVerifyTaskWithoutNamespaceResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunVerifyTaskWithoutNamespaceResult>()
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

    TSharedPtr<FJsonObject> FRunVerifyTaskWithoutNamespaceResult::ToJson() const
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