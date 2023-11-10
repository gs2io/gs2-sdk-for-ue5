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

#include "Experience/Request/DeleteThresholdMasterRequest.h"

namespace Gs2::Experience::Request
{
    FDeleteThresholdMasterRequest::FDeleteThresholdMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ThresholdNameValue(TOptional<FString>())
    {
    }

    FDeleteThresholdMasterRequest::FDeleteThresholdMasterRequest(
        const FDeleteThresholdMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ThresholdNameValue(From.ThresholdNameValue)
    {
    }

    TSharedPtr<FDeleteThresholdMasterRequest> FDeleteThresholdMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteThresholdMasterRequest> FDeleteThresholdMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteThresholdMasterRequest> FDeleteThresholdMasterRequest::WithThresholdName(
        const TOptional<FString> ThresholdName
    )
    {
        this->ThresholdNameValue = ThresholdName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteThresholdMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteThresholdMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteThresholdMasterRequest::GetThresholdName() const
    {
        return ThresholdNameValue;
    }

    TSharedPtr<FDeleteThresholdMasterRequest> FDeleteThresholdMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteThresholdMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithThresholdName(Data->HasField("thresholdName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("thresholdName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteThresholdMasterRequest::ToJson() const
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