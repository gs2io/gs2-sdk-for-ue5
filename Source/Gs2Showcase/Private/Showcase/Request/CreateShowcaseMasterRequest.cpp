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

#include "Showcase/Request/CreateShowcaseMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FCreateShowcaseMasterRequest::FCreateShowcaseMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DisplayItemsValue(nullptr),
        SalesPeriodEventIdValue(TOptional<FString>())
    {
    }

    FCreateShowcaseMasterRequest::FCreateShowcaseMasterRequest(
        const FCreateShowcaseMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DisplayItemsValue(From.DisplayItemsValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue)
    {
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FDisplayItemMaster>>> FCreateShowcaseMasterRequest::GetDisplayItems() const
    {
        if (!DisplayItemsValue.IsValid())
        {
            return nullptr;
        }
        return DisplayItemsValue;
    }

    TOptional<FString> FCreateShowcaseMasterRequest::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }

    TSharedPtr<FCreateShowcaseMasterRequest> FCreateShowcaseMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateShowcaseMasterRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDisplayItems(Data->HasField("displayItems") ? [Data]() -> TSharedPtr<TArray<Model::FDisplayItemMasterPtr>>
              {
                  auto v = MakeShared<TArray<Model::FDisplayItemMasterPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("displayItems") && Data->HasTypedField<EJson::Array>("displayItems"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("displayItems"))
                      {
                          v->Add(Model::FDisplayItemMaster::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithSalesPeriodEventId(Data->HasField("salesPeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateShowcaseMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DisplayItemsValue != nullptr && DisplayItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DisplayItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("displayItems", v);
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesPeriodEventId", SalesPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}