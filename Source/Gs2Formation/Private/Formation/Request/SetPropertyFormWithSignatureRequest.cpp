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

#include "Formation/Request/SetPropertyFormWithSignatureRequest.h"

namespace Gs2::Formation::Request
{
    FSetPropertyFormWithSignatureRequest::FSetPropertyFormWithSignatureRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        PropertyFormModelNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        SlotsValue(nullptr),
        KeyIdValue(TOptional<FString>())
    {
    }

    FSetPropertyFormWithSignatureRequest::FSetPropertyFormWithSignatureRequest(
        const FSetPropertyFormWithSignatureRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        PropertyFormModelNameValue(From.PropertyFormModelNameValue),
        PropertyIdValue(From.PropertyIdValue),
        SlotsValue(From.SlotsValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithPropertyFormModelName(
        const TOptional<FString> PropertyFormModelName
    )
    {
        this->PropertyFormModelNameValue = PropertyFormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetPropertyFormModelName() const
    {
        return PropertyFormModelNameValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> FSetPropertyFormWithSignatureRequest::GetSlots() const
    {
        if (!SlotsValue.IsValid())
        {
            return nullptr;
        }
        return SlotsValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FSetPropertyFormWithSignatureRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetPropertyFormWithSignatureRequest> FSetPropertyFormWithSignatureRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetPropertyFormWithSignatureRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
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
          ->WithSlots(Data->HasField("slots") ? [Data]() -> TSharedPtr<TArray<Model::FSlotWithSignaturePtr>>
              {
                  auto v = MakeShared<TArray<Model::FSlotWithSignaturePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("slots") && Data->HasTypedField<EJson::Array>("slots"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("slots"))
                      {
                          v->Add(Model::FSlotWithSignature::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetPropertyFormWithSignatureRequest::ToJson() const
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
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}