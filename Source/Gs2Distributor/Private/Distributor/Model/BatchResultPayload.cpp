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

#include "Distributor/Model/BatchResultPayload.h"

namespace Gs2::Distributor::Model
{
    FBatchResultPayload::FBatchResultPayload():
        RequestIdValue(TOptional<FString>()),
        StatusCodeValue(TOptional<int32>()),
        ResultPayloadValue(TOptional<FString>())
    {
    }

    FBatchResultPayload::FBatchResultPayload(
        const FBatchResultPayload& From
    ):
        RequestIdValue(From.RequestIdValue),
        StatusCodeValue(From.StatusCodeValue),
        ResultPayloadValue(From.ResultPayloadValue)
    {
    }

    TSharedPtr<FBatchResultPayload> FBatchResultPayload::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FBatchResultPayload> FBatchResultPayload::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FBatchResultPayload> FBatchResultPayload::WithResultPayload(
        const TOptional<FString> ResultPayload
    )
    {
        this->ResultPayloadValue = ResultPayload;
        return SharedThis(this);
    }
    TOptional<FString> FBatchResultPayload::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<int32> FBatchResultPayload::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FBatchResultPayload::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FBatchResultPayload::GetResultPayload() const
    {
        return ResultPayloadValue;
    }

    TSharedPtr<FBatchResultPayload> FBatchResultPayload::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBatchResultPayload>()
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), v))
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
            ->WithResultPayload(Data->HasField(ANSI_TO_TCHAR("resultPayload")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resultPayload"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FBatchResultPayload::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("requestId", RequestIdValue.GetValue());
        }
        if (StatusCodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("statusCode", StatusCodeValue.GetValue());
        }
        if (ResultPayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("resultPayload", ResultPayloadValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBatchResultPayload::TypeName = "BatchResultPayload";
}