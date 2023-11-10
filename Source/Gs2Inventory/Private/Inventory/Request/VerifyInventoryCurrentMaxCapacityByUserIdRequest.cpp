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

#include "Inventory/Request/VerifyInventoryCurrentMaxCapacityByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FVerifyInventoryCurrentMaxCapacityByUserIdRequest::FVerifyInventoryCurrentMaxCapacityByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        CurrentInventoryMaxCapacityValue(TOptional<int32>())
    {
    }

    FVerifyInventoryCurrentMaxCapacityByUserIdRequest::FVerifyInventoryCurrentMaxCapacityByUserIdRequest(
        const FVerifyInventoryCurrentMaxCapacityByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        InventoryNameValue(From.InventoryNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        CurrentInventoryMaxCapacityValue(From.CurrentInventoryMaxCapacityValue)
    {
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithCurrentInventoryMaxCapacity(
        const TOptional<int32> CurrentInventoryMaxCapacity
    )
    {
        this->CurrentInventoryMaxCapacityValue = CurrentInventoryMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<int32> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetCurrentInventoryMaxCapacity() const
    {
        return CurrentInventoryMaxCapacityValue;
    }

    FString FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetCurrentInventoryMaxCapacityString() const
    {
        if (!CurrentInventoryMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryMaxCapacityValue.GetValue());
    }

    TOptional<FString> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityByUserIdRequest> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyInventoryCurrentMaxCapacityByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
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

    TSharedPtr<FJsonObject> FVerifyInventoryCurrentMaxCapacityByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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