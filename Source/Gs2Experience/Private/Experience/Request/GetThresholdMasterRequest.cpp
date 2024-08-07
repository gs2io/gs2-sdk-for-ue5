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

#include "Experience/Request/GetThresholdMasterRequest.h"

namespace Gs2::Experience::Request
{
    FGetThresholdMasterRequest::FGetThresholdMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ThresholdNameValue(TOptional<FString>())
    {
    }

    FGetThresholdMasterRequest::FGetThresholdMasterRequest(
        const FGetThresholdMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ThresholdNameValue(From.ThresholdNameValue)
    {
    }

    TSharedPtr<FGetThresholdMasterRequest> FGetThresholdMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetThresholdMasterRequest> FGetThresholdMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetThresholdMasterRequest> FGetThresholdMasterRequest::WithThresholdName(
        const TOptional<FString> ThresholdName
    )
    {
        this->ThresholdNameValue = ThresholdName;
        return SharedThis(this);
    }

    TOptional<FString> FGetThresholdMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetThresholdMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetThresholdMasterRequest::GetThresholdName() const
    {
        return ThresholdNameValue;
    }

    TSharedPtr<FGetThresholdMasterRequest> FGetThresholdMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetThresholdMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithThresholdName(Data->HasField(ANSI_TO_TCHAR("thresholdName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("thresholdName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetThresholdMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (ThresholdNameValue.IsSet())
        {
            JsonRootObject->SetStringField("thresholdName", ThresholdNameValue.GetValue());
        }
        return JsonRootObject;
    }
}