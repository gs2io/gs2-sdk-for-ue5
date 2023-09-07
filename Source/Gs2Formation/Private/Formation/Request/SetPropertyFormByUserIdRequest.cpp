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

#include "Formation/Request/SetPropertyFormByUserIdRequest.h"

namespace Gs2::Formation::Request
{
    FSetPropertyFormByUserIdRequest::FSetPropertyFormByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PropertyFormModelNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        SlotsValue(nullptr)
    {
    }

    FSetPropertyFormByUserIdRequest::FSetPropertyFormByUserIdRequest(
        const FSetPropertyFormByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        PropertyFormModelNameValue(From.PropertyFormModelNameValue),
        PropertyIdValue(From.PropertyIdValue),
        SlotsValue(From.SlotsValue)
    {
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithPropertyFormModelName(
        const TOptional<FString> PropertyFormModelName
    )
    {
        this->PropertyFormModelNameValue = PropertyFormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetPropertyFormModelName() const
    {
        return PropertyFormModelNameValue;
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> FSetPropertyFormByUserIdRequest::GetSlots() const
    {
        if (!SlotsValue.IsValid())
        {
            return nullptr;
        }
        return SlotsValue;
    }

    TOptional<FString> FSetPropertyFormByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetPropertyFormByUserIdRequest> FSetPropertyFormByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetPropertyFormByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
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
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithSlots(Data->HasField("slots") ? [Data]() -> TSharedPtr<TArray<Model::FSlotPtr>>
              {
                  auto v = MakeShared<TArray<Model::FSlotPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("slots") && Data->HasTypedField<EJson::Array>("slots"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("slots"))
                      {
                          v->Add(Model::FSlot::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetPropertyFormByUserIdRequest::ToJson() const
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
        if (PropertyFormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyFormModelName", PropertyFormModelNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}