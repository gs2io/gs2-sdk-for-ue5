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

#include "Formation/Request/AcquireActionsToFormPropertiesRequest.h"

namespace Gs2::Formation::Request
{
    FAcquireActionsToFormPropertiesRequest::FAcquireActionsToFormPropertiesRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MoldNameValue(TOptional<FString>()),
        IndexValue(TOptional<int32>()),
        AcquireActionValue(nullptr),
        ConfigValue(nullptr)
    {
    }

    FAcquireActionsToFormPropertiesRequest::FAcquireActionsToFormPropertiesRequest(
        const FAcquireActionsToFormPropertiesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        MoldNameValue(From.MoldNameValue),
        IndexValue(From.IndexValue),
        AcquireActionValue(From.AcquireActionValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithMoldName(
        const TOptional<FString> MoldName
    )
    {
        this->MoldNameValue = MoldName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithAcquireAction(
        const TSharedPtr<Model::FAcquireAction> AcquireAction
    )
    {
        this->AcquireActionValue = AcquireAction;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FAcquireActionsToFormPropertiesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesRequest::GetMoldName() const
    {
        return MoldNameValue;
    }

    TOptional<int32> FAcquireActionsToFormPropertiesRequest::GetIndex() const
    {
        return IndexValue;
    }

    FString FAcquireActionsToFormPropertiesRequest::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), IndexValue.GetValue());
    }

    TSharedPtr<Model::FAcquireAction> FAcquireActionsToFormPropertiesRequest::GetAcquireAction() const
    {
        if (!AcquireActionValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionConfig>>> FAcquireActionsToFormPropertiesRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FAcquireActionsToFormPropertiesRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FAcquireActionsToFormPropertiesRequest> FAcquireActionsToFormPropertiesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionsToFormPropertiesRequest>()
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
            ->WithMoldName(Data->HasField("moldName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("moldName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIndex(Data->HasField("index") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("index", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FAcquireActionsToFormPropertiesRequest::ToJson() const
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
        if (MoldNameValue.IsSet())
        {
            JsonRootObject->SetStringField("moldName", MoldNameValue.GetValue());
        }
        if (IndexValue.IsSet())
        {
            JsonRootObject->SetNumberField("index", IndexValue.GetValue());
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