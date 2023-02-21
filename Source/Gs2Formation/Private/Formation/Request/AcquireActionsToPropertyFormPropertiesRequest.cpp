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

#include "Formation/Request/AcquireActionsToPropertyFormPropertiesRequest.h"

namespace Gs2::Formation::Request
{
    FAcquireActionsToPropertyFormPropertiesRequest::FAcquireActionsToPropertyFormPropertiesRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        FormModelNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        AcquireActionValue(nullptr),
        ConfigValue(nullptr)
    {
    }

    FAcquireActionsToPropertyFormPropertiesRequest::FAcquireActionsToPropertyFormPropertiesRequest(
        const FAcquireActionsToPropertyFormPropertiesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        FormModelNameValue(From.FormModelNameValue),
        PropertyIdValue(From.PropertyIdValue),
        AcquireActionValue(From.AcquireActionValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithFormModelName(
        const TOptional<FString> FormModelName
    )
    {
        this->FormModelNameValue = FormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithAcquireAction(
        const TSharedPtr<Model::FAcquireAction> AcquireAction
    )
    {
        this->AcquireActionValue = AcquireAction;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetFormModelName() const
    {
        return FormModelNameValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<Model::FAcquireAction> FAcquireActionsToPropertyFormPropertiesRequest::GetAcquireAction() const
    {
        if (!AcquireActionValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionConfig>>> FAcquireActionsToPropertyFormPropertiesRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionsToPropertyFormPropertiesRequest>()
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
            ->WithFormModelName(Data->HasField("formModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("formModelName", v))
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
          ->WithAcquireAction(Data->HasField("acquireAction") ? [Data]() -> Model::FAcquireActionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("acquireAction"))
                  {
                      return nullptr;
                  }
                  return Model::FAcquireAction::FromJson(Data->GetObjectField("acquireAction"));
             }() : nullptr)
          ->WithConfig(Data->HasField("config") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("config") && Data->HasTypedField<EJson::Array>("config"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("config"))
                      {
                          v->Add(Model::FAcquireActionConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAcquireActionsToPropertyFormPropertiesRequest::ToJson() const
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
        if (FormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("formModelName", FormModelNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (AcquireActionValue != nullptr && AcquireActionValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquireAction", AcquireActionValue->ToJson());
        }
        if (ConfigValue != nullptr && ConfigValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConfigValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("config", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}