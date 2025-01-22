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

#include "Distributor/Model/BatchRequestPayload.h"

namespace Gs2::Distributor::Model
{
    FBatchRequestPayload::FBatchRequestPayload():
        RequestIdValue(TOptional<FString>()),
        ServiceValue(TOptional<FString>()),
        MethodNameValue(TOptional<FString>()),
        ParameterValue(TOptional<FString>())
    {
    }

    FBatchRequestPayload::FBatchRequestPayload(
        const FBatchRequestPayload& From
    ):
        RequestIdValue(From.RequestIdValue),
        ServiceValue(From.ServiceValue),
        MethodNameValue(From.MethodNameValue),
        ParameterValue(From.ParameterValue)
    {
    }

    TSharedPtr<FBatchRequestPayload> FBatchRequestPayload::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FBatchRequestPayload> FBatchRequestPayload::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FBatchRequestPayload> FBatchRequestPayload::WithMethodName(
        const TOptional<FString> MethodName
    )
    {
        this->MethodNameValue = MethodName;
        return SharedThis(this);
    }

    TSharedPtr<FBatchRequestPayload> FBatchRequestPayload::WithParameter(
        const TOptional<FString> Parameter
    )
    {
        this->ParameterValue = Parameter;
        return SharedThis(this);
    }
    TOptional<FString> FBatchRequestPayload::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<FString> FBatchRequestPayload::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FBatchRequestPayload::GetMethodName() const
    {
        return MethodNameValue;
    }
    TOptional<FString> FBatchRequestPayload::GetParameter() const
    {
        return ParameterValue;
    }

    TSharedPtr<FBatchRequestPayload> FBatchRequestPayload::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBatchRequestPayload>()
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithService(Data->HasField(ANSI_TO_TCHAR("service")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("service"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMethodName(Data->HasField(ANSI_TO_TCHAR("methodName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("methodName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithParameter(Data->HasField(ANSI_TO_TCHAR("parameter")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("parameter"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FBatchRequestPayload::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("requestId", RequestIdValue.GetValue());
        }
        if (ServiceValue.IsSet())
        {
            JsonRootObject->SetStringField("service", ServiceValue.GetValue());
        }
        if (MethodNameValue.IsSet())
        {
            JsonRootObject->SetStringField("methodName", MethodNameValue.GetValue());
        }
        if (ParameterValue.IsSet())
        {
            JsonRootObject->SetStringField("parameter", ParameterValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBatchRequestPayload::TypeName = "BatchRequestPayload";
}