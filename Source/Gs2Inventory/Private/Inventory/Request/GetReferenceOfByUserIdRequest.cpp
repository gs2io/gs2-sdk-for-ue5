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

#include "Inventory/Request/GetReferenceOfByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FGetReferenceOfByUserIdRequest::FGetReferenceOfByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        ItemSetNameValue(TOptional<FString>()),
        ReferenceOfValue(TOptional<FString>())
    {
    }

    FGetReferenceOfByUserIdRequest::FGetReferenceOfByUserIdRequest(
        const FGetReferenceOfByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        UserIdValue(From.UserIdValue),
        ItemNameValue(From.ItemNameValue),
        ItemSetNameValue(From.ItemSetNameValue),
        ReferenceOfValue(From.ReferenceOfValue)
    {
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithItemSetName(
        const TOptional<FString> ItemSetName
    )
    {
        this->ItemSetNameValue = ItemSetName;
        return SharedThis(this);
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::WithReferenceOf(
        const TOptional<FString> ReferenceOf
    )
    {
        this->ReferenceOfValue = ReferenceOf;
        return SharedThis(this);
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetItemSetName() const
    {
        return ItemSetNameValue;
    }

    TOptional<FString> FGetReferenceOfByUserIdRequest::GetReferenceOf() const
    {
        return ReferenceOfValue;
    }

    TSharedPtr<FGetReferenceOfByUserIdRequest> FGetReferenceOfByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetReferenceOfByUserIdRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetReferenceOfByUserIdRequest::ToJson() const
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
        return JsonRootObject;
    }
}