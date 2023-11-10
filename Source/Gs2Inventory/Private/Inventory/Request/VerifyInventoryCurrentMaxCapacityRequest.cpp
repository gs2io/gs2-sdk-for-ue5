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

#include "Inventory/Request/VerifyInventoryCurrentMaxCapacityRequest.h"

namespace Gs2::Inventory::Request
{
    FVerifyInventoryCurrentMaxCapacityRequest::FVerifyInventoryCurrentMaxCapacityRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        CurrentInventoryMaxCapacityValue(TOptional<int32>())
    {
    }

    FVerifyInventoryCurrentMaxCapacityRequest::FVerifyInventoryCurrentMaxCapacityRequest(
        const FVerifyInventoryCurrentMaxCapacityRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        InventoryNameValue(From.InventoryNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CurrentInventoryMaxCapacityValue(From.CurrentInventoryMaxCapacityValue)
    {
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithCurrentInventoryMaxCapacity(
        const TOptional<int32> CurrentInventoryMaxCapacity
    )
    {
        this->CurrentInventoryMaxCapacityValue = CurrentInventoryMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyInventoryCurrentMaxCapacityRequest::GetCurrentInventoryMaxCapacity() const
    {
        return CurrentInventoryMaxCapacityValue;
    }

    FString FVerifyInventoryCurrentMaxCapacityRequest::GetCurrentInventoryMaxCapacityString() const
    {
        if (!CurrentInventoryMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryMaxCapacityValue.GetValue());
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityRequest> FVerifyInventoryCurrentMaxCapacityRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyInventoryCurrentMaxCapacityRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInventoryName(Data->HasField("inventoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("inventoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField("verifyType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("verifyType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCurrentInventoryMaxCapacity(Data->HasField("currentInventoryMaxCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("currentInventoryMaxCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyInventoryCurrentMaxCapacityRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (InventoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryName", InventoryNameValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (CurrentInventoryMaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("currentInventoryMaxCapacity", CurrentInventoryMaxCapacityValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}