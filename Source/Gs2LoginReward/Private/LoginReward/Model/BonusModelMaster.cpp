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

#include "LoginReward/Model/BonusModelMaster.h"

namespace Gs2::LoginReward::Model
{
    FBonusModelMaster::FBonusModelMaster():
        BonusModelIdValue(TOptional<FString>()),
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
        MissedReceiveReliefConsumeActionsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FBonusModelMaster::FBonusModelMaster(
        const FBonusModelMaster& From
    ):
        BonusModelIdValue(From.BonusModelIdValue),
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
        MissedReceiveReliefConsumeActionsValue(From.MissedReceiveReliefConsumeActionsValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithBonusModelId(
        const TOptional<FString> BonusModelId
    )
    {
        this->BonusModelIdValue = BonusModelId;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithPeriodEventId(
        const TOptional<FString> PeriodEventId
    )
    {
        this->PeriodEventIdValue = PeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithRepeat(
        const TOptional<FString> Repeat
    )
    {
        this->RepeatValue = Repeat;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithMissedReceiveRelief(
        const TOptional<FString> MissedReceiveRelief
    )
    {
        this->MissedReceiveReliefValue = MissedReceiveRelief;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithMissedReceiveReliefVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> MissedReceiveReliefVerifyActions
    )
    {
        this->MissedReceiveReliefVerifyActionsValue = MissedReceiveReliefVerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithMissedReceiveReliefConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActions
    )
    {
        this->MissedReceiveReliefConsumeActionsValue = MissedReceiveReliefConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FBonusModelMaster::GetBonusModelId() const
    {
        return BonusModelIdValue;
    }
    TOptional<FString> FBonusModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBonusModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FBonusModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FBonusModelMaster::GetMode() const
    {
        return ModeValue;
    }
    TOptional<FString> FBonusModelMaster::GetPeriodEventId() const
    {
        return PeriodEventIdValue;
    }
    TOptional<int32> FBonusModelMaster::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FBonusModelMaster::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FBonusModelMaster::GetRepeat() const
    {
        return RepeatValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FBonusModelMaster::GetRewards() const
    {
        return RewardsValue;
    }
    TOptional<FString> FBonusModelMaster::GetMissedReceiveRelief() const
    {
        return MissedReceiveReliefValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FBonusModelMaster::GetMissedReceiveReliefVerifyActions() const
    {
        return MissedReceiveReliefVerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FBonusModelMaster::GetMissedReceiveReliefConsumeActions() const
    {
        return MissedReceiveReliefConsumeActionsValue;
    }
    TOptional<int64> FBonusModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FBonusModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FBonusModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FBonusModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FBonusModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FBonusModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FBonusModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModelMaster::GetBonusModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBonusModelMaster> FBonusModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBonusModelMaster>()
            ->WithBonusModelId(Data->HasField(ANSI_TO_TCHAR("bonusModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("bonusModelId"), v))
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
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FBonusModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BonusModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("bonusModelId", BonusModelIdValue.GetValue());
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
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FBonusModelMaster::TypeName = "BonusModelMaster";
}