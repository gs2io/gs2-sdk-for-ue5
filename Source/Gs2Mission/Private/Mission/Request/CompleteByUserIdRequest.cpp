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

#include "Mission/Request/CompleteByUserIdRequest.h"

namespace Gs2::Mission::Request
{
    FCompleteByUserIdRequest::FCompleteByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        MissionTaskNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ConfigValue(nullptr)
    {
    }

    FCompleteByUserIdRequest::FCompleteByUserIdRequest(
        const FCompleteByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        MissionTaskNameValue(From.MissionTaskNameValue),
        UserIdValue(From.UserIdValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithMissionTaskName(
        const TOptional<FString> MissionTaskName
    )
    {
        this->MissionTaskNameValue = MissionTaskName;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCompleteByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCompleteByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCompleteByUserIdRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FCompleteByUserIdRequest::GetMissionTaskName() const
    {
        return MissionTaskNameValue;
    }

    TOptional<FString> FCompleteByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FCompleteByUserIdRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FCompleteByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCompleteByUserIdRequest> FCompleteByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCompleteByUserIdRequest>()
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
            ->WithMissionGroupName(Data->HasField("missionGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("missionGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMissionTaskName(Data->HasField("missionTaskName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("missionTaskName", v))
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
          ->WithConfig(Data->HasField("config") ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("config") && Data->HasTypedField<EJson::Array>("config"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("config"))
                      {
                          v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCompleteByUserIdRequest::ToJson() const
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
        if (MissionGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupName", MissionGroupNameValue.GetValue());
        }
        if (MissionTaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionTaskName", MissionTaskNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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