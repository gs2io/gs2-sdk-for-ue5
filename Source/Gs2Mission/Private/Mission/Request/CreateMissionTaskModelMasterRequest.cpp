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
        CounterNameValue(TOptional<FString>()),
        TargetResetTypeValue(TOptional<FString>()),
        TargetValueValue(TOptional<int64>()),
        CompleteAcquireActionsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        PremiseMissionTaskNameValue(TOptional<FString>())
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
        CounterNameValue(From.CounterNameValue),
        TargetResetTypeValue(From.TargetResetTypeValue),
        TargetValueValue(From.TargetValueValue),
        CompleteAcquireActionsValue(From.CompleteAcquireActionsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        PremiseMissionTaskNameValue(From.PremiseMissionTaskNameValue)
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

    TSharedPtr<FCreateMissionTaskModelMasterRequest> FCreateMissionTaskModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateMissionTaskModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMissionGroupName(Data->HasField("missionGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("missionGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
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
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("counterName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetResetType(Data->HasField("targetResetType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("targetResetType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetValue(Data->HasField("targetValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("targetValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
          ->WithCompleteAcquireActions(Data->HasField("completeAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("completeAcquireActions") && Data->HasTypedField<EJson::Array>("completeAcquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("completeAcquireActions"))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPremiseMissionTaskName(Data->HasField("premiseMissionTaskName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("premiseMissionTaskName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
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
        return JsonRootObject;
    }
}