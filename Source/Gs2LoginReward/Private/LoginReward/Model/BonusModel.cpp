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

#include "LoginReward/Model/BonusModel.h"

namespace Gs2::LoginReward::Model
{
    FBonusModel::FBonusModel():
        BonusModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        PeriodEventIdValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        RepeatValue(TOptional<FString>()),
        RewardsValue(nullptr),
        MissedReceiveReliefValue(TOptional<FString>()),
        MissedReceiveReliefConsumeActionsValue(nullptr)
    {
    }

    FBonusModel::FBonusModel(
        const FBonusModel& From
    ):
        BonusModelIdValue(From.BonusModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ModeValue(From.ModeValue),
        PeriodEventIdValue(From.PeriodEventIdValue),
        ResetHourValue(From.ResetHourValue),
        RepeatValue(From.RepeatValue),
        RewardsValue(From.RewardsValue),
        MissedReceiveReliefValue(From.MissedReceiveReliefValue),
        MissedReceiveReliefConsumeActionsValue(From.MissedReceiveReliefConsumeActionsValue)
    {
    }

    TSharedPtr<FBonusModel> FBonusModel::WithBonusModelId(
        const TOptional<FString> BonusModelId
    )
    {
        this->BonusModelIdValue = BonusModelId;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithPeriodEventId(
        const TOptional<FString> PeriodEventId
    )
    {
        this->PeriodEventIdValue = PeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithRepeat(
        const TOptional<FString> Repeat
    )
    {
        this->RepeatValue = Repeat;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithMissedReceiveRelief(
        const TOptional<FString> MissedReceiveRelief
    )
    {
        this->MissedReceiveReliefValue = MissedReceiveRelief;
        return SharedThis(this);
    }

    TSharedPtr<FBonusModel> FBonusModel::WithMissedReceiveReliefConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActions
    )
    {
        this->MissedReceiveReliefConsumeActionsValue = MissedReceiveReliefConsumeActions;
        return SharedThis(this);
    }
    TOptional<FString> FBonusModel::GetBonusModelId() const
    {
        return BonusModelIdValue;
    }
    TOptional<FString> FBonusModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBonusModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FBonusModel::GetMode() const
    {
        return ModeValue;
    }
    TOptional<FString> FBonusModel::GetPeriodEventId() const
    {
        return PeriodEventIdValue;
    }
    TOptional<int32> FBonusModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FBonusModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FBonusModel::GetRepeat() const
    {
        return RepeatValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FBonusModel::GetRewards() const
    {
        return RewardsValue;
    }
    TOptional<FString> FBonusModel::GetMissedReceiveRelief() const
    {
        return MissedReceiveReliefValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FBonusModel::GetMissedReceiveReliefConsumeActions() const
    {
        return MissedReceiveReliefConsumeActionsValue;
    }

    TOptional<FString> FBonusModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBonusModel::GetBonusModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):bonusModel:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBonusModel> FBonusModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBonusModel>()
            ->WithBonusModelId(Data->HasField("bonusModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("bonusModelId", v))
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
            ->WithMode(Data->HasField("mode") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("mode", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPeriodEventId(Data->HasField("periodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("periodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetHour(Data->HasField("resetHour") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("resetHour", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeat(Data->HasField("repeat") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("repeat", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRewards(Data->HasField("rewards") ? [Data]() -> TSharedPtr<TArray<Model::FRewardPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRewardPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("rewards") && Data->HasTypedField<EJson::Array>("rewards"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("rewards"))
                        {
                            v->Add(Model::FReward::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRewardPtr>>())
            ->WithMissedReceiveRelief(Data->HasField("missedReceiveRelief") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("missedReceiveRelief", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMissedReceiveReliefConsumeActions(Data->HasField("missedReceiveReliefConsumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("missedReceiveReliefConsumeActions") && Data->HasTypedField<EJson::Array>("missedReceiveReliefConsumeActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("missedReceiveReliefConsumeActions"))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>());
    }

    TSharedPtr<FJsonObject> FBonusModel::ToJson() const
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

    FString FBonusModel::TypeName = "BonusModel";
}