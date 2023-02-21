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

#include "Quest/Model/QuestModel.h"

namespace Gs2::Quest::Model
{
    FQuestModel::FQuestModel():
        QuestModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ContentsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        FirstCompleteAcquireActionsValue(nullptr),
        ConsumeActionsValue(nullptr),
        FailedAcquireActionsValue(nullptr),
        PremiseQuestNamesValue(nullptr)
    {
    }

    FQuestModel::FQuestModel(
        const FQuestModel& From
    ):
        QuestModelIdValue(From.QuestModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ContentsValue(From.ContentsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        FirstCompleteAcquireActionsValue(From.FirstCompleteAcquireActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        FailedAcquireActionsValue(From.FailedAcquireActionsValue),
        PremiseQuestNamesValue(From.PremiseQuestNamesValue)
    {
    }

    TSharedPtr<FQuestModel> FQuestModel::WithQuestModelId(
        const TOptional<FString> QuestModelId
    )
    {
        this->QuestModelIdValue = QuestModelId;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithContents(
        const TSharedPtr<TArray<TSharedPtr<Model::FContents>>> Contents
    )
    {
        this->ContentsValue = Contents;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithFirstCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActions
    )
    {
        this->FirstCompleteAcquireActionsValue = FirstCompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithFailedAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActions
    )
    {
        this->FailedAcquireActionsValue = FailedAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FQuestModel> FQuestModel::WithPremiseQuestNames(
        const TSharedPtr<TArray<FString>> PremiseQuestNames
    )
    {
        this->PremiseQuestNamesValue = PremiseQuestNames;
        return SharedThis(this);
    }
    TOptional<FString> FQuestModel::GetQuestModelId() const
    {
        return QuestModelIdValue;
    }
    TOptional<FString> FQuestModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FQuestModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FContents>>> FQuestModel::GetContents() const
    {
        return ContentsValue;
    }
    TOptional<FString> FQuestModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FQuestModel::GetFirstCompleteAcquireActions() const
    {
        return FirstCompleteAcquireActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FQuestModel::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FQuestModel::GetFailedAcquireActions() const
    {
        return FailedAcquireActionsValue;
    }
    TSharedPtr<TArray<FString>> FQuestModel::GetPremiseQuestNames() const
    {
        return PremiseQuestNamesValue;
    }

    TOptional<FString> FQuestModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):group:(?<questGroupName>.+):quest:(?<questName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FQuestModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):group:(?<questGroupName>.+):quest:(?<questName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FQuestModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):group:(?<questGroupName>.+):quest:(?<questName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FQuestModel::GetQuestGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):group:(?<questGroupName>.+):quest:(?<questName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FQuestModel::GetQuestNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):group:(?<questGroupName>.+):quest:(?<questName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FQuestModel> FQuestModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQuestModel>()
            ->WithQuestModelId(Data->HasField("questModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("questModelId", v))
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
            ->WithContents(Data->HasField("contents") ? [Data]() -> TSharedPtr<TArray<Model::FContentsPtr>>
                {
                    auto v = MakeShared<TArray<Model::FContentsPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("contents") && Data->HasTypedField<EJson::Array>("contents"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("contents"))
                        {
                            v->Add(Model::FContents::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFirstCompleteAcquireActions(Data->HasField("firstCompleteAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("firstCompleteAcquireActions") && Data->HasTypedField<EJson::Array>("firstCompleteAcquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("firstCompleteAcquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithConsumeActions(Data->HasField("consumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("consumeActions") && Data->HasTypedField<EJson::Array>("consumeActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("consumeActions"))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithFailedAcquireActions(Data->HasField("failedAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("failedAcquireActions") && Data->HasTypedField<EJson::Array>("failedAcquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("failedAcquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithPremiseQuestNames(Data->HasField("premiseQuestNames") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("premiseQuestNames") && Data->HasTypedField<EJson::Array>("premiseQuestNames"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("premiseQuestNames"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FQuestModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (QuestModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("questModelId", QuestModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ContentsValue != nullptr && ContentsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ContentsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("contents", v);
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        if (FirstCompleteAcquireActionsValue != nullptr && FirstCompleteAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *FirstCompleteAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("firstCompleteAcquireActions", v);
        }
        if (ConsumeActionsValue != nullptr && ConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeActions", v);
        }
        if (FailedAcquireActionsValue != nullptr && FailedAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *FailedAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("failedAcquireActions", v);
        }
        if (PremiseQuestNamesValue != nullptr && PremiseQuestNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PremiseQuestNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("premiseQuestNames", v);
        }
        return JsonRootObject;
    }

    FString FQuestModel::TypeName = "QuestModel";
}