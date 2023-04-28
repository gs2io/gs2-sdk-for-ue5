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

#include "Mission/Model/MissionTaskModel.h"

namespace Gs2::Mission::Model
{
    FMissionTaskModel::FMissionTaskModel():
        MissionTaskIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        TargetValueValue(TOptional<int64>()),
        CompleteAcquireActionsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        PremiseMissionTaskNameValue(TOptional<FString>())
    {
    }

    FMissionTaskModel::FMissionTaskModel(
        const FMissionTaskModel& From
    ):
        MissionTaskIdValue(From.MissionTaskIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        CounterNameValue(From.CounterNameValue),
        TargetValueValue(From.TargetValueValue),
        CompleteAcquireActionsValue(From.CompleteAcquireActionsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        PremiseMissionTaskNameValue(From.PremiseMissionTaskNameValue)
    {
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithMissionTaskId(
        const TOptional<FString> MissionTaskId
    )
    {
        this->MissionTaskIdValue = MissionTaskId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithTargetValue(
        const TOptional<int64> TargetValue
    )
    {
        this->TargetValueValue = TargetValue;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::WithPremiseMissionTaskName(
        const TOptional<FString> PremiseMissionTaskName
    )
    {
        this->PremiseMissionTaskNameValue = PremiseMissionTaskName;
        return SharedThis(this);
    }
    TOptional<FString> FMissionTaskModel::GetMissionTaskId() const
    {
        return MissionTaskIdValue;
    }
    TOptional<FString> FMissionTaskModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMissionTaskModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FMissionTaskModel::GetCounterName() const
    {
        return CounterNameValue;
    }
    TOptional<int64> FMissionTaskModel::GetTargetValue() const
    {
        return TargetValueValue;
    }

    FString FMissionTaskModel::GetTargetValueString() const
    {
        if (!TargetValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetValueValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FMissionTaskModel::GetCompleteAcquireActions() const
    {
        return CompleteAcquireActionsValue;
    }
    TOptional<FString> FMissionTaskModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TOptional<FString> FMissionTaskModel::GetPremiseMissionTaskName() const
    {
        return PremiseMissionTaskNameValue;
    }

    TOptional<FString> FMissionTaskModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetMissionGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionTaskModel::GetMissionTaskNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+):missionTaskModel:(?<missionTaskName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMissionTaskModel> FMissionTaskModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMissionTaskModel>()
            ->WithMissionTaskId(Data->HasField("missionTaskId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("missionTaskId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("counterName", v))
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
                    FString v;
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPremiseMissionTaskName(Data->HasField("premiseMissionTaskName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("premiseMissionTaskName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FMissionTaskModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MissionTaskIdValue.IsSet())
        {
            JsonRootObject->SetStringField("missionTaskId", MissionTaskIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
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

    FString FMissionTaskModel::TypeName = "MissionTaskModel";
}