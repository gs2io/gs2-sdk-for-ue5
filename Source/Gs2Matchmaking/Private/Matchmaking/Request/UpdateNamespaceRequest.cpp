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

#include "Matchmaking/Request/UpdateNamespaceRequest.h"

namespace Gs2::Matchmaking::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        EnableRatingValue(TOptional<bool>()),
        CreateGatheringTriggerTypeValue(TOptional<FString>()),
        CreateGatheringTriggerRealtimeNamespaceIdValue(TOptional<FString>()),
        CreateGatheringTriggerScriptIdValue(TOptional<FString>()),
        CompleteMatchmakingTriggerTypeValue(TOptional<FString>()),
        CompleteMatchmakingTriggerRealtimeNamespaceIdValue(TOptional<FString>()),
        CompleteMatchmakingTriggerScriptIdValue(TOptional<FString>()),
        ChangeRatingScriptValue(nullptr),
        JoinNotificationValue(nullptr),
        LeaveNotificationValue(nullptr),
        CompleteNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        EnableRatingValue(From.EnableRatingValue),
        CreateGatheringTriggerTypeValue(From.CreateGatheringTriggerTypeValue),
        CreateGatheringTriggerRealtimeNamespaceIdValue(From.CreateGatheringTriggerRealtimeNamespaceIdValue),
        CreateGatheringTriggerScriptIdValue(From.CreateGatheringTriggerScriptIdValue),
        CompleteMatchmakingTriggerTypeValue(From.CompleteMatchmakingTriggerTypeValue),
        CompleteMatchmakingTriggerRealtimeNamespaceIdValue(From.CompleteMatchmakingTriggerRealtimeNamespaceIdValue),
        CompleteMatchmakingTriggerScriptIdValue(From.CompleteMatchmakingTriggerScriptIdValue),
        ChangeRatingScriptValue(From.ChangeRatingScriptValue),
        JoinNotificationValue(From.JoinNotificationValue),
        LeaveNotificationValue(From.LeaveNotificationValue),
        CompleteNotificationValue(From.CompleteNotificationValue),
        LogSettingValue(From.LogSettingValue)
    {
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithEnableRating(
        const TOptional<bool> EnableRating
    )
    {
        this->EnableRatingValue = EnableRating;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCreateGatheringTriggerType(
        const TOptional<FString> CreateGatheringTriggerType
    )
    {
        this->CreateGatheringTriggerTypeValue = CreateGatheringTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCreateGatheringTriggerRealtimeNamespaceId(
        const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId
    )
    {
        this->CreateGatheringTriggerRealtimeNamespaceIdValue = CreateGatheringTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCreateGatheringTriggerScriptId(
        const TOptional<FString> CreateGatheringTriggerScriptId
    )
    {
        this->CreateGatheringTriggerScriptIdValue = CreateGatheringTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCompleteMatchmakingTriggerType(
        const TOptional<FString> CompleteMatchmakingTriggerType
    )
    {
        this->CompleteMatchmakingTriggerTypeValue = CompleteMatchmakingTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCompleteMatchmakingTriggerRealtimeNamespaceId(
        const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId
    )
    {
        this->CompleteMatchmakingTriggerRealtimeNamespaceIdValue = CompleteMatchmakingTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCompleteMatchmakingTriggerScriptId(
        const TOptional<FString> CompleteMatchmakingTriggerScriptId
    )
    {
        this->CompleteMatchmakingTriggerScriptIdValue = CompleteMatchmakingTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangeRatingScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRatingScript
    )
    {
        this->ChangeRatingScriptValue = ChangeRatingScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithJoinNotification(
        const TSharedPtr<Model::FNotificationSetting> JoinNotification
    )
    {
        this->JoinNotificationValue = JoinNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLeaveNotification(
        const TSharedPtr<Model::FNotificationSetting> LeaveNotification
    )
    {
        this->LeaveNotificationValue = LeaveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCompleteNotification(
        const TSharedPtr<Model::FNotificationSetting> CompleteNotification
    )
    {
        this->CompleteNotificationValue = CompleteNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FUpdateNamespaceRequest::GetEnableRating() const
    {
        return EnableRatingValue;
    }

    FString FUpdateNamespaceRequest::GetEnableRatingString() const
    {
        if (!EnableRatingValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableRatingValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCreateGatheringTriggerType() const
    {
        return CreateGatheringTriggerTypeValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCreateGatheringTriggerRealtimeNamespaceId() const
    {
        return CreateGatheringTriggerRealtimeNamespaceIdValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCreateGatheringTriggerScriptId() const
    {
        return CreateGatheringTriggerScriptIdValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCompleteMatchmakingTriggerType() const
    {
        return CompleteMatchmakingTriggerTypeValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCompleteMatchmakingTriggerRealtimeNamespaceId() const
    {
        return CompleteMatchmakingTriggerRealtimeNamespaceIdValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetCompleteMatchmakingTriggerScriptId() const
    {
        return CompleteMatchmakingTriggerScriptIdValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetChangeRatingScript() const
    {
        if (!ChangeRatingScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRatingScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetJoinNotification() const
    {
        if (!JoinNotificationValue.IsValid())
        {
            return nullptr;
        }
        return JoinNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetLeaveNotification() const
    {
        if (!LeaveNotificationValue.IsValid())
        {
            return nullptr;
        }
        return LeaveNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetCompleteNotification() const
    {
        if (!CompleteNotificationValue.IsValid())
        {
            return nullptr;
        }
        return CompleteNotificationValue;
    }

    TSharedPtr<Model::FLogSetting> FUpdateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateNamespaceRequest>()
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEnableRating(Data->HasField("enableRating") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("enableRating", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithCreateGatheringTriggerType(Data->HasField("createGatheringTriggerType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("createGatheringTriggerType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCreateGatheringTriggerRealtimeNamespaceId(Data->HasField("createGatheringTriggerRealtimeNamespaceId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("createGatheringTriggerRealtimeNamespaceId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCreateGatheringTriggerScriptId(Data->HasField("createGatheringTriggerScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("createGatheringTriggerScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerType(Data->HasField("completeMatchmakingTriggerType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("completeMatchmakingTriggerType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerRealtimeNamespaceId(Data->HasField("completeMatchmakingTriggerRealtimeNamespaceId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("completeMatchmakingTriggerRealtimeNamespaceId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerScriptId(Data->HasField("completeMatchmakingTriggerScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("completeMatchmakingTriggerScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithChangeRatingScript(Data->HasField("changeRatingScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeRatingScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("changeRatingScript"));
             }() : nullptr)
          ->WithJoinNotification(Data->HasField("joinNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("joinNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("joinNotification"));
             }() : nullptr)
          ->WithLeaveNotification(Data->HasField("leaveNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("leaveNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("leaveNotification"));
             }() : nullptr)
          ->WithCompleteNotification(Data->HasField("completeNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("completeNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("completeNotification"));
             }() : nullptr)
          ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("logSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateNamespaceRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (EnableRatingValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableRating", EnableRatingValue.GetValue());
        }
        if (CreateGatheringTriggerTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerType", CreateGatheringTriggerTypeValue.GetValue());
        }
        if (CreateGatheringTriggerRealtimeNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerRealtimeNamespaceId", CreateGatheringTriggerRealtimeNamespaceIdValue.GetValue());
        }
        if (CreateGatheringTriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("createGatheringTriggerScriptId", CreateGatheringTriggerScriptIdValue.GetValue());
        }
        if (CompleteMatchmakingTriggerTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerType", CompleteMatchmakingTriggerTypeValue.GetValue());
        }
        if (CompleteMatchmakingTriggerRealtimeNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerRealtimeNamespaceId", CompleteMatchmakingTriggerRealtimeNamespaceIdValue.GetValue());
        }
        if (CompleteMatchmakingTriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeMatchmakingTriggerScriptId", CompleteMatchmakingTriggerScriptIdValue.GetValue());
        }
        if (ChangeRatingScriptValue != nullptr && ChangeRatingScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRatingScript", ChangeRatingScriptValue->ToJson());
        }
        if (JoinNotificationValue != nullptr && JoinNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("joinNotification", JoinNotificationValue->ToJson());
        }
        if (LeaveNotificationValue != nullptr && LeaveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("leaveNotification", LeaveNotificationValue->ToJson());
        }
        if (CompleteNotificationValue != nullptr && CompleteNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("completeNotification", CompleteNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}