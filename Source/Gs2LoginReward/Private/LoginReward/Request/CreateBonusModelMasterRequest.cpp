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

#include "LoginReward/Request/CreateBonusModelMasterRequest.h"

namespace Gs2::LoginReward::Request
{
    FCreateBonusModelMasterRequest::FCreateBonusModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        PeriodEventIdValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        RepeatValue(TOptional<FString>()),
        RewardsValue(nullptr),
        MissedReceiveReliefValue(TOptional<FString>()),
        MissedReceiveReliefVerifyActionsValue(nullptr),
        MissedReceiveReliefConsumeActionsValue(nullptr)
    {
    }

    FCreateBonusModelMasterRequest::FCreateBonusModelMasterRequest(
        const FCreateBonusModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ModeValue(From.ModeValue),
        PeriodEventIdValue(From.PeriodEventIdValue),
        ResetHourValue(From.ResetHourValue),
        RepeatValue(From.RepeatValue),
        RewardsValue(From.RewardsValue),
        MissedReceiveReliefValue(From.MissedReceiveReliefValue),
        MissedReceiveReliefVerifyActionsValue(From.MissedReceiveReliefVerifyActionsValue),
        MissedReceiveReliefConsumeActionsValue(From.MissedReceiveReliefConsumeActionsValue)
    {
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithPeriodEventId(
        const TOptional<FString> PeriodEventId
    )
    {
        this->PeriodEventIdValue = PeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithRepeat(
        const TOptional<FString> Repeat
    )
    {
        this->RepeatValue = Repeat;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithMissedReceiveRelief(
        const TOptional<FString> MissedReceiveRelief
    )
    {
        this->MissedReceiveReliefValue = MissedReceiveRelief;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithMissedReceiveReliefVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> MissedReceiveReliefVerifyActions
    )
    {
        this->MissedReceiveReliefVerifyActionsValue = MissedReceiveReliefVerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::WithMissedReceiveReliefConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActions
    )
    {
        this->MissedReceiveReliefConsumeActionsValue = MissedReceiveReliefConsumeActions;
        return SharedThis(this);
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetMode() const
    {
        return ModeValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetPeriodEventId() const
    {
        return PeriodEventIdValue;
    }

    TOptional<int32> FCreateBonusModelMasterRequest::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FCreateBonusModelMasterRequest::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetRepeat() const
    {
        return RepeatValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FCreateBonusModelMasterRequest::GetRewards() const
    {
        if (!RewardsValue.IsValid())
        {
            return nullptr;
        }
        return RewardsValue;
    }

    TOptional<FString> FCreateBonusModelMasterRequest::GetMissedReceiveRelief() const
    {
        return MissedReceiveReliefValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FCreateBonusModelMasterRequest::GetMissedReceiveReliefVerifyActions() const
    {
        if (!MissedReceiveReliefVerifyActionsValue.IsValid())
        {
            return nullptr;
        }
        return MissedReceiveReliefVerifyActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FCreateBonusModelMasterRequest::GetMissedReceiveReliefConsumeActions() const
    {
        if (!MissedReceiveReliefConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return MissedReceiveReliefConsumeActionsValue;
    }

    TSharedPtr<FCreateBonusModelMasterRequest> FCreateBonusModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateBonusModelMasterRequest>()
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
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMode(Data->HasField(ANSI_TO_TCHAR("mode")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("mode"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPeriodEventId(Data->HasField(ANSI_TO_TCHAR("periodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("periodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetHour(Data->HasField(ANSI_TO_TCHAR("resetHour")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("resetHour"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithRepeat(Data->HasField(ANSI_TO_TCHAR("repeat")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repeat"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithRewards(Data->HasField(ANSI_TO_TCHAR("rewards")) ? [Data]() -> TSharedPtr<TArray<Model::FRewardPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRewardPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rewards")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("rewards")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("rewards")))
                      {
                          v->Add(Model::FReward::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FRewardPtr>>())
            ->WithMissedReceiveRelief(Data->HasField(ANSI_TO_TCHAR("missedReceiveRelief")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missedReceiveRelief"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithMissedReceiveReliefVerifyActions(Data->HasField(ANSI_TO_TCHAR("missedReceiveReliefVerifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("missedReceiveReliefVerifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("missedReceiveReliefVerifyActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("missedReceiveReliefVerifyActions")))
                      {
                          v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
          ->WithMissedReceiveReliefConsumeActions(Data->HasField(ANSI_TO_TCHAR("missedReceiveReliefConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("missedReceiveReliefConsumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("missedReceiveReliefConsumeActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("missedReceiveReliefConsumeActions")))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConsumeActionPtr>>());
    }

    TSharedPtr<FJsonObject> FCreateBonusModelMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ModeValue.IsSet())
        {
            JsonRootObject->SetStringField("mode", ModeValue.GetValue());
        }
        if (PeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("periodEventId", PeriodEventIdValue.GetValue());
        }
        if (ResetHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetHour", ResetHourValue.GetValue());
        }
        if (RepeatValue.IsSet())
        {
            JsonRootObject->SetStringField("repeat", RepeatValue.GetValue());
        }
        if (RewardsValue != nullptr && RewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("rewards", v);
        }
        if (MissedReceiveReliefValue.IsSet())
        {
            JsonRootObject->SetStringField("missedReceiveRelief", MissedReceiveReliefValue.GetValue());
        }
        if (MissedReceiveReliefVerifyActionsValue != nullptr && MissedReceiveReliefVerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MissedReceiveReliefVerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("missedReceiveReliefVerifyActions", v);
        }
        if (MissedReceiveReliefConsumeActionsValue != nullptr && MissedReceiveReliefConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MissedReceiveReliefConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("missedReceiveReliefConsumeActions", v);
        }
        return JsonRootObject;
    }
}