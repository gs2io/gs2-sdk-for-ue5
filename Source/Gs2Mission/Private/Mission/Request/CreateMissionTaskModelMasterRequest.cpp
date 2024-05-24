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

#include "Mission/Request/CreateMissionTaskModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FCreateMissionTaskModelMasterRequest::FCreateMissionTaskModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
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

    FCreateMissionTaskModelMasterRequest::FCreateMissionTaskModelMasterRequest(
        const FCreateMissionTaskModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        NameValue(From.NameValue),
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

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithVerifyCompleteType(
        const TOptional<FString> VerifyCompleteType
    )
    {
        this->VerifyCompleteTypeValue = VerifyCompleteType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithTargetCounter(
        const TSharedPtr<Model::FTargetCounterModel> TargetCounter
    )
    {
        this->TargetCounterValue = TargetCounter;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithVerifyCompleteConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> VerifyCompleteConsumeActions
    )
    {
        this->VerifyCompleteConsumeActionsValue = VerifyCompleteConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithPremiseMissionTaskName(
        const TOptional<FString> PremiseMissionTaskName
    )
    {
        this->PremiseMissionTaskNameValue = PremiseMissionTaskName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithTargetResetType(
        const TOptional<FString> TargetResetType
    )
    {
        this->TargetResetTypeValue = TargetResetType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::WithTargetValue(
        const TOptional<int64> TargetValue
    )
    {
        this->TargetValueValue = TargetValue;
        return SharedThis(this);
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetVerifyCompleteType() const
    {
        return VerifyCompleteTypeValue;
    }

    TSharedPtr<Model::FTargetCounterModel> FCreateMissionTaskModelMasterRequest::GetTargetCounter() const
    {
        if (!TargetCounterValue.IsValid())
        {
            return nullptr;
        }
        return TargetCounterValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FCreateMissionTaskModelMasterRequest::GetVerifyCompleteConsumeActions() const
    {
        if (!VerifyCompleteConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return VerifyCompleteConsumeActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FCreateMissionTaskModelMasterRequest::GetCompleteAcquireActions() const
    {
        if (!CompleteAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return CompleteAcquireActionsValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetPremiseMissionTaskName() const
    {
        return PremiseMissionTaskNameValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FCreateMissionTaskModelMasterRequest::GetTargetResetType() const
    {
        return TargetResetTypeValue;
    }

    TOptional<int64> FCreateMissionTaskModelMasterRequest::GetTargetValue() const
    {
        return TargetValueValue;
    }

    FString FCreateMissionTaskModelMasterRequest::GetTargetValueString() const
    {
        if (!TargetValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetValueValue.GetValue());
    }

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateMissionTaskModelMasterRequest>()
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
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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
          ->WithVerifyCompleteConsumeActions(Data->HasField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyCompleteConsumeActions")))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
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

    TSharedPtr<FJsonObject> FCreateMissionTaskModelMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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