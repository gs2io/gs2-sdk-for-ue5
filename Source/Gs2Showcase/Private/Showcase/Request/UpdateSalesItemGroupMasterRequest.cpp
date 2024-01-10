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

#include "Showcase/Request/UpdateSalesItemGroupMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FUpdateSalesItemGroupMasterRequest::FUpdateSalesItemGroupMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SalesItemGroupNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SalesItemNamesValue(nullptr)
    {
    }

    FUpdateSalesItemGroupMasterRequest::FUpdateSalesItemGroupMasterRequest(
        const FUpdateSalesItemGroupMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SalesItemGroupNameValue(From.SalesItemGroupNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        SalesItemNamesValue(From.SalesItemNamesValue)
    {
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithSalesItemGroupName(
        const TOptional<FString> SalesItemGroupName
    )
    {
        this->SalesItemGroupNameValue = SalesItemGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::WithSalesItemNames(
        const TSharedPtr<TArray<FString>> SalesItemNames
    )
    {
        this->SalesItemNamesValue = SalesItemNames;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateSalesItemGroupMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateSalesItemGroupMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateSalesItemGroupMasterRequest::GetSalesItemGroupName() const
    {
        return SalesItemGroupNameValue;
    }

    TOptional<FString> FUpdateSalesItemGroupMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateSalesItemGroupMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<FString>> FUpdateSalesItemGroupMasterRequest::GetSalesItemNames() const
    {
        if (!SalesItemNamesValue.IsValid())
        {
            return nullptr;
        }
        return SalesItemNamesValue;
    }

    TSharedPtr<FUpdateSalesItemGroupMasterRequest> FUpdateSalesItemGroupMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateSalesItemGroupMasterRequest>()
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
            ->WithSalesItemGroupName(Data->HasField("salesItemGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("salesItemGroupName", v))
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
          ->WithSalesItemNames(Data->HasField("salesItemNames") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("salesItemNames") && Data->HasTypedField<EJson::Array>("salesItemNames"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("salesItemNames"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FUpdateSalesItemGroupMasterRequest::ToJson() const
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
        if (SalesItemGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemGroupName", SalesItemGroupNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SalesItemNamesValue != nullptr && SalesItemNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SalesItemNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("salesItemNames", v);
        }
        return JsonRootObject;
    }
}