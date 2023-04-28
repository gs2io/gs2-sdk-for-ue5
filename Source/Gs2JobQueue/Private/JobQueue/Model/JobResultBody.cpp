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

#include "JobQueue/Model/JobResultBody.h"

namespace Gs2::JobQueue::Model
{
    FJobResultBody::FJobResultBody():
        TryNumberValue(TOptional<int32>()),
        StatusCodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>()),
        TryAtValue(TOptional<int64>())
    {
    }

    FJobResultBody::FJobResultBody(
        const FJobResultBody& From
    ):
        TryNumberValue(From.TryNumberValue),
        StatusCodeValue(From.StatusCodeValue),
        ResultValue(From.ResultValue),
        TryAtValue(From.TryAtValue)
    {
    }

    TSharedPtr<FJobResultBody> FJobResultBody::WithTryNumber(
        const TOptional<int32> TryNumber
    )
    {
        this->TryNumberValue = TryNumber;
        return SharedThis(this);
    }

    TSharedPtr<FJobResultBody> FJobResultBody::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FJobResultBody> FJobResultBody::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FJobResultBody> FJobResultBody::WithTryAt(
        const TOptional<int64> TryAt
    )
    {
        this->TryAtValue = TryAt;
        return SharedThis(this);
    }
    TOptional<int32> FJobResultBody::GetTryNumber() const
    {
        return TryNumberValue;
    }

    FString FJobResultBody::GetTryNumberString() const
    {
        if (!TryNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TryNumberValue.GetValue());
    }
    TOptional<int32> FJobResultBody::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FJobResultBody::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FJobResultBody::GetResult() const
    {
        return ResultValue;
    }
    TOptional<int64> FJobResultBody::GetTryAt() const
    {
        return TryAtValue;
    }

    FString FJobResultBody::GetTryAtString() const
    {
        if (!TryAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TryAtValue.GetValue());
    }

    TSharedPtr<FJobResultBody> FJobResultBody::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJobResultBody>()
            ->WithTryNumber(Data->HasField("tryNumber") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("tryNumber", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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
                    FString v;
                    if (Data->TryGetStringField("result", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTryAt(Data->HasField("tryAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("tryAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FJobResultBody::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TryNumberValue.IsSet())
        {
            JsonRootObject->SetNumberField("tryNumber", TryNumberValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        if (TryAtValue.IsSet())
        {
            JsonRootObject->SetStringField("tryAt", FString::Printf(TEXT("%lld"), TryAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FJobResultBody::TypeName = "JobResultBody";
}