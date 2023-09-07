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

#include "Formation/Request/UpdatePropertyFormModelMasterRequest.h"

namespace Gs2::Formation::Request
{
    FUpdatePropertyFormModelMasterRequest::FUpdatePropertyFormModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        PropertyFormModelNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SlotsValue(nullptr)
    {
    }

    FUpdatePropertyFormModelMasterRequest::FUpdatePropertyFormModelMasterRequest(
        const FUpdatePropertyFormModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PropertyFormModelNameValue(From.PropertyFormModelNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        SlotsValue(From.SlotsValue)
    {
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithPropertyFormModelName(
        const TOptional<FString> PropertyFormModelName
    )
    {
        this->PropertyFormModelNameValue = PropertyFormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }

    TOptional<FString> FUpdatePropertyFormModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdatePropertyFormModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdatePropertyFormModelMasterRequest::GetPropertyFormModelName() const
    {
        return PropertyFormModelNameValue;
    }

    TOptional<FString> FUpdatePropertyFormModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdatePropertyFormModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> FUpdatePropertyFormModelMasterRequest::GetSlots() const
    {
        if (!SlotsValue.IsValid())
        {
            return nullptr;
        }
        return SlotsValue;
    }

    TSharedPtr<FUpdatePropertyFormModelMasterRequest> FUpdatePropertyFormModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdatePropertyFormModelMasterRequest>()
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
            ->WithPropertyFormModelName(Data->HasField("propertyFormModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyFormModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithSlots(Data->HasField("slots") ? [Data]() -> TSharedPtr<TArray<Model::FSlotModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FSlotModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("slots") && Data->HasTypedField<EJson::Array>("slots"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("slots"))
                      {
                          v->Add(Model::FSlotModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdatePropertyFormModelMasterRequest::ToJson() const
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
        if (PropertyFormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyFormModelName", PropertyFormModelNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SlotsValue != nullptr && SlotsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SlotsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("slots", v);
        }
        return JsonRootObject;
    }
}