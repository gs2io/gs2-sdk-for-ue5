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

#include "Stamina/Request/DeleteStaminaModelMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FDeleteStaminaModelMasterRequest::FDeleteStaminaModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>())
    {
    }

    FDeleteStaminaModelMasterRequest::FDeleteStaminaModelMasterRequest(
        const FDeleteStaminaModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StaminaNameValue(From.StaminaNameValue)
    {
    }

    TSharedPtr<FDeleteStaminaModelMasterRequest> FDeleteStaminaModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStaminaModelMasterRequest> FDeleteStaminaModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStaminaModelMasterRequest> FDeleteStaminaModelMasterRequest::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteStaminaModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteStaminaModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteStaminaModelMasterRequest::GetStaminaName() const
    {
        return StaminaNameValue;
    }

    TSharedPtr<FDeleteStaminaModelMasterRequest> FDeleteStaminaModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteStaminaModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStaminaName(Data->HasField("staminaName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("staminaName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteStaminaModelMasterRequest::ToJson() const
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
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        return JsonRootObject;
    }
}