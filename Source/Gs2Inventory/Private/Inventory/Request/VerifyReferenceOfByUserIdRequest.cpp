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

#include "Inventory/Request/VerifyReferenceOfByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FVerifyReferenceOfByUserIdRequest::FVerifyReferenceOfByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        ItemSetNameValue(TOptional<FString>()),
        ReferenceOfValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>())
    {
    }

    FVerifyReferenceOfByUserIdRequest::FVerifyReferenceOfByUserIdRequest(
        const FVerifyReferenceOfByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        UserIdValue(From.UserIdValue),
        ItemNameValue(From.ItemNameValue),
        ItemSetNameValue(From.ItemSetNameValue),
        ReferenceOfValue(From.ReferenceOfValue),
        VerifyTypeValue(From.VerifyTypeValue)
    {
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithItemSetName(
        const TOptional<FString> ItemSetName
    )
    {
        this->ItemSetNameValue = ItemSetName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithReferenceOf(
        const TOptional<FString> ReferenceOf
    )
    {
        this->ReferenceOfValue = ReferenceOf;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetItemSetName() const
    {
        return ItemSetNameValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetReferenceOf() const
    {
        return ReferenceOfValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyReferenceOfByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyReferenceOfByUserIdRequest> FVerifyReferenceOfByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyReferenceOfByUserIdRequest>()
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
            ->WithInventoryName(Data->HasField("inventoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("inventoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithItemName(Data->HasField("itemName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("itemName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithItemSetName(Data->HasField("itemSetName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("itemSetName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithReferenceOf(Data->HasField("referenceOf") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("referenceOf", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField("verifyType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("verifyType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyReferenceOfByUserIdRequest::ToJson() const
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
        if (InventoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryName", InventoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("itemName", ItemNameValue.GetValue());
        }
        if (ItemSetNameValue.IsSet())
        {
            JsonRootObject->SetStringField("itemSetName", ItemSetNameValue.GetValue());
        }
        if (ReferenceOfValue.IsSet())
        {
            JsonRootObject->SetStringField("referenceOf", ReferenceOfValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyType", VerifyTypeValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}