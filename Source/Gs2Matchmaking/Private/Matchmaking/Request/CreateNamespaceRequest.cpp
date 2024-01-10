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

#include "Matchmaking/Request/CreateNamespaceRequest.h"

namespace Gs2::Matchmaking::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
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
        ChangeRatingNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
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
        ChangeRatingNotificationValue(From.ChangeRatingNotificationValue),
        LogSettingValue(From.LogSettingValue)
    {
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithEnableRating(
        const TOptional<bool> EnableRating
    )
    {
        this->EnableRatingValue = EnableRating;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateGatheringTriggerType(
        const TOptional<FString> CreateGatheringTriggerType
    )
    {
        this->CreateGatheringTriggerTypeValue = CreateGatheringTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateGatheringTriggerRealtimeNamespaceId(
        const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId
    )
    {
        this->CreateGatheringTriggerRealtimeNamespaceIdValue = CreateGatheringTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateGatheringTriggerScriptId(
        const TOptional<FString> CreateGatheringTriggerScriptId
    )
    {
        this->CreateGatheringTriggerScriptIdValue = CreateGatheringTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCompleteMatchmakingTriggerType(
        const TOptional<FString> CompleteMatchmakingTriggerType
    )
    {
        this->CompleteMatchmakingTriggerTypeValue = CompleteMatchmakingTriggerType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCompleteMatchmakingTriggerRealtimeNamespaceId(
        const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId
    )
    {
        this->CompleteMatchmakingTriggerRealtimeNamespaceIdValue = CompleteMatchmakingTriggerRealtimeNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCompleteMatchmakingTriggerScriptId(
        const TOptional<FString> CompleteMatchmakingTriggerScriptId
    )
    {
        this->CompleteMatchmakingTriggerScriptIdValue = CompleteMatchmakingTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeRatingScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRatingScript
    )
    {
        this->ChangeRatingScriptValue = ChangeRatingScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithJoinNotification(
        const TSharedPtr<Model::FNotificationSetting> JoinNotification
    )
    {
        this->JoinNotificationValue = JoinNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLeaveNotification(
        const TSharedPtr<Model::FNotificationSetting> LeaveNotification
    )
    {
        this->LeaveNotificationValue = LeaveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCompleteNotification(
        const TSharedPtr<Model::FNotificationSetting> CompleteNotification
    )
    {
        this->CompleteNotificationValue = CompleteNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeRatingNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangeRatingNotification
    )
    {
        this->ChangeRatingNotificationValue = ChangeRatingNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetEnableRating() const
    {
        return EnableRatingValue;
    }

    FString FCreateNamespaceRequest::GetEnableRatingString() const
    {
        if (!EnableRatingValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableRatingValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FCreateNamespaceRequest::GetCreateGatheringTriggerType() const
    {
        return CreateGatheringTriggerTypeValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetCreateGatheringTriggerRealtimeNamespaceId() const
    {
        return CreateGatheringTriggerRealtimeNamespaceIdValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetCreateGatheringTriggerScriptId() const
    {
        return CreateGatheringTriggerScriptIdValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetCompleteMatchmakingTriggerType() const
    {
        return CompleteMatchmakingTriggerTypeValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetCompleteMatchmakingTriggerRealtimeNamespaceId() const
    {
        return CompleteMatchmakingTriggerRealtimeNamespaceIdValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetCompleteMatchmakingTriggerScriptId() const
    {
        return CompleteMatchmakingTriggerScriptIdValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetChangeRatingScript() const
    {
        if (!ChangeRatingScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRatingScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetJoinNotification() const
    {
        if (!JoinNotificationValue.IsValid())
        {
            return nullptr;
        }
        return JoinNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetLeaveNotification() const
    {
        if (!LeaveNotificationValue.IsValid())
        {
            return nullptr;
        }
        return LeaveNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetCompleteNotification() const
    {
        if (!CompleteNotificationValue.IsValid())
        {
            return nullptr;
        }
        return CompleteNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetChangeRatingNotification() const
    {
        if (!ChangeRatingNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRatingNotificationValue;
    }

    TSharedPtr<Model::FLogSetting> FCreateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateNamespaceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
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
                  FString v("");
                    if (Data->TryGetStringField("createGatheringTriggerType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCreateGatheringTriggerRealtimeNamespaceId(Data->HasField("createGatheringTriggerRealtimeNamespaceId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("createGatheringTriggerRealtimeNamespaceId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCreateGatheringTriggerScriptId(Data->HasField("createGatheringTriggerScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("createGatheringTriggerScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerType(Data->HasField("completeMatchmakingTriggerType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("completeMatchmakingTriggerType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerRealtimeNamespaceId(Data->HasField("completeMatchmakingTriggerRealtimeNamespaceId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("completeMatchmakingTriggerRealtimeNamespaceId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCompleteMatchmakingTriggerScriptId(Data->HasField("completeMatchmakingTriggerScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
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
          ->WithChangeRatingNotification(Data->HasField("changeRatingNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeRatingNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("changeRatingNotification"));
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

    TSharedPtr<FJsonObject> FCreateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        if (ChangeRatingNotificationValue != nullptr && ChangeRatingNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRatingNotification", ChangeRatingNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}