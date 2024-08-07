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
        PropertyFormModelNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        AcquireActionValue(nullptr),
        ConfigValue(nullptr),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FAcquireActionsToPropertyFormPropertiesRequest::FAcquireActionsToPropertyFormPropertiesRequest(
        const FAcquireActionsToPropertyFormPropertiesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        PropertyFormModelNameValue(From.PropertyFormModelNameValue),
        PropertyIdValue(From.PropertyIdValue),
        AcquireActionValue(From.AcquireActionValue),
        ConfigValue(From.ConfigValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
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

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithPropertyFormModelName(
        const TOptional<FString> PropertyFormModelName
    )
    {
        this->PropertyFormModelNameValue = PropertyFormModelName;
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
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FAcquireActionsToPropertyFormPropertiesRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
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

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetPropertyFormModelName() const
    {
        return PropertyFormModelNameValue;
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

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FAcquireActionsToPropertyFormPropertiesRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FAcquireActionsToPropertyFormPropertiesRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
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
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyFormModelName(Data->HasField(ANSI_TO_TCHAR("propertyFormModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyFormModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField(ANSI_TO_TCHAR("propertyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAcquireAction(Data->HasField(ANSI_TO_TCHAR("acquireAction")) ? [Data]() -> Model::FAcquireActionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireAction")))
                  {
                      return nullptr;
                  }
                  return Model::FAcquireAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acquireAction")));
              }() : nullptr)
          ->WithConfig(Data->HasField(ANSI_TO_TCHAR("config")) ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("config")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("config")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("config")))
                      {
                          v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConfigPtr>>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
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
        if (PropertyFormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyFormModelName", PropertyFormModelNameValue.GetValue());
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
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}