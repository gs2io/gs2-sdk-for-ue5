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

#include "Mission/Request/UpdateMissionTaskModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FUpdateMissionTaskModelMasterRequest::FUpdateMissionTaskModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        MissionTaskNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        VerifyCompleteTypeValue(TOptional<FString>()),
        TargetCounterValue(nullptr),
        VerifyCompleteConsumeActionsValue(nullptr),
        CompleteAcquireActionsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        PremiseMissionTaskNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        TargetResetTypeValue(TOptional<FString>()),
        TargetValueValue(TOptional<int64>())
    {
    }

    FUpdateMissionTaskModelMasterRequest::FUpdateMissionTaskModelMasterRequest(
        const FUpdateMissionTaskModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        MissionTaskNameValue(From.MissionTaskNameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        VerifyCompleteTypeValue(From.VerifyCompleteTypeValue),
        TargetCounterValue(From.TargetCounterValue),
        VerifyCompleteConsumeActionsValue(From.VerifyCompleteConsumeActionsValue),
        CompleteAcquireActionsValue(From.CompleteAcquireActionsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        PremiseMissionTaskNameValue(From.PremiseMissionTaskNameValue),
        CounterNameValue(From.CounterNameValue),
        TargetResetTypeValue(From.TargetResetTypeValue),
        TargetValueValue(From.TargetValueValue)
    {
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithMissionTaskName(
        const TOptional<FString> MissionTaskName
    )
    {
        this->MissionTaskNameValue = MissionTaskName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithVerifyCompleteType(
        const TOptional<FString> VerifyCompleteType
    )
    {
        this->VerifyCompleteTypeValue = VerifyCompleteType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithTargetCounter(
        const TSharedPtr<Model::FTargetCounterModel> TargetCounter
    )
    {
        this->TargetCounterValue = TargetCounter;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithVerifyCompleteConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyCompleteConsumeActions
    )
    {
        this->VerifyCompleteConsumeActionsValue = VerifyCompleteConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithPremiseMissionTaskName(
        const TOptional<FString> PremiseMissionTaskName
    )
    {
        this->PremiseMissionTaskNameValue = PremiseMissionTaskName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithTargetResetType(
        const TOptional<FString> TargetResetType
    )
    {
        this->TargetResetTypeValue = TargetResetType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::WithTargetValue(
        const TOptional<int64> TargetValue
    )
    {
        this->TargetValueValue = TargetValue;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetMissionTaskName() const
    {
        return MissionTaskNameValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetVerifyCompleteType() const
    {
        return VerifyCompleteTypeValue;
    }

    TSharedPtr<Model::FTargetCounterModel> FUpdateMissionTaskModelMasterRequest::GetTargetCounter() const
    {
        if (!TargetCounterValue.IsValid())
        {
            return nullptr;
        }
        return TargetCounterValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FUpdateMissionTaskModelMasterRequest::GetVerifyCompleteConsumeActions() const
    {
        if (!VerifyCompleteConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return VerifyCompleteConsumeActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateMissionTaskModelMasterRequest::GetCompleteAcquireActions() const
    {
        if (!CompleteAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return CompleteAcquireActionsValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetPremiseMissionTaskName() const
    {
        return PremiseMissionTaskNameValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FUpdateMissionTaskModelMasterRequest::GetTargetResetType() const
    {
        return TargetResetTypeValue;
    }

    TOptional<int64> FUpdateMissionTaskModelMasterRequest::GetTargetValue() const
    {
        return TargetValueValue;
    }

    FString FUpdateMissionTaskModelMasterRequest::GetTargetValueString() const
    {
        if (!TargetValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetValueValue.GetValue());
    }

    TSharedPtr<FUpdateMissionTaskModelMasterRequest> FUpdateMissionTaskModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateMissionTaskModelMasterRequest>()
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
            ->WithMissionGroupName(Data->HasField(ANSI_TO_TCHAR("missionGroupName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missionGroupName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMissionTaskName(Data->HasField(ANSI_TO_TCHAR("missionTaskName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missionTaskName"), v))
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyCompleteType(Data->HasField(ANSI_TO_TCHAR("verifyCompleteType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyCompleteType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTargetCounter(Data->HasField(ANSI_TO_TCHAR("targetCounter")) ? [Data]() -> Model::FTargetCounterModelPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetCounter")))
                  {
                      return nullptr;
                  }
                  return Model::FTargetCounterModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetCounter")));
              }() : nullptr)
          ->WithVerifyCompleteConsumeActions(Data->HasField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                      {
                          v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
          ->WithCompleteAcquireActions(Data->HasField(ANSI_TO_TCHAR("completeAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("completeAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("completeAcquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("completeAcquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithChallengePeriodEventId(Data->HasField(ANSI_TO_TCHAR("challengePeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengePeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPremiseMissionTaskName(Data->HasField(ANSI_TO_TCHAR("premiseMissionTaskName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("premiseMissionTaskName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCounterName(Data->HasField(ANSI_TO_TCHAR("counterName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("counterName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetResetType(Data->HasField(ANSI_TO_TCHAR("targetResetType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetResetType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetValue(Data->HasField(ANSI_TO_TCHAR("targetValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("targetValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FUpdateMissionTaskModelMasterRequest::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (VerifyCompleteTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyCompleteType", VerifyCompleteTypeValue.GetValue());
        }
        if (TargetCounterValue != nullptr && TargetCounterValue.IsValid())
        {
            JsonRootObject->SetObjectField("targetCounter", TargetCounterValue->ToJson());
        }
        if (VerifyCompleteConsumeActionsValue != nullptr && VerifyCompleteConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyCompleteConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyCompleteConsumeActions", v);
        }
        if (CompleteAcquireActionsValue != nullptr && CompleteAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CompleteAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("completeAcquireActions", v);
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        if (PremiseMissionTaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField("premiseMissionTaskName", PremiseMissionTaskNameValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        if (TargetResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("targetResetType", TargetResetTypeValue.GetValue());
        }
        if (TargetValueValue.IsSet())
        {
            JsonRootObject->SetStringField("targetValue", FString::Printf(TEXT("%lld"), TargetValueValue.GetValue()));
        }
        return JsonRootObject;
    }
}