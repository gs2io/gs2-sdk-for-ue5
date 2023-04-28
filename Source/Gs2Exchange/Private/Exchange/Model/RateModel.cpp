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

#include "Exchange/Model/RateModel.h"

namespace Gs2::Exchange::Model
{
    FRateModel::FRateModel():
        RateModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ConsumeActionsValue(nullptr),
        TimingTypeValue(TOptional<FString>()),
        LockTimeValue(TOptional<int32>()),
        EnableSkipValue(TOptional<bool>()),
        SkipConsumeActionsValue(nullptr),
        AcquireActionsValue(nullptr)
    {
    }

    FRateModel::FRateModel(
        const FRateModel& From
    ):
        RateModelIdValue(From.RateModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        TimingTypeValue(From.TimingTypeValue),
        LockTimeValue(From.LockTimeValue),
        EnableSkipValue(From.EnableSkipValue),
        SkipConsumeActionsValue(From.SkipConsumeActionsValue),
        AcquireActionsValue(From.AcquireActionsValue)
    {
    }

    TSharedPtr<FRateModel> FRateModel::WithRateModelId(
        const TOptional<FString> RateModelId
    )
    {
        this->RateModelIdValue = RateModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithTimingType(
        const TOptional<FString> TimingType
    )
    {
        this->TimingTypeValue = TimingType;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithLockTime(
        const TOptional<int32> LockTime
    )
    {
        this->LockTimeValue = LockTime;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithEnableSkip(
        const TOptional<bool> EnableSkip
    )
    {
        this->EnableSkipValue = EnableSkip;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithSkipConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> SkipConsumeActions
    )
    {
        this->SkipConsumeActionsValue = SkipConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FRateModel::GetRateModelId() const
    {
        return RateModelIdValue;
    }
    TOptional<FString> FRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FRateModel::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TOptional<FString> FRateModel::GetTimingType() const
    {
        return TimingTypeValue;
    }
    TOptional<int32> FRateModel::GetLockTime() const
    {
        return LockTimeValue;
    }

    FString FRateModel::GetLockTimeString() const
    {
        if (!LockTimeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LockTimeValue.GetValue());
    }
    TOptional<bool> FRateModel::GetEnableSkip() const
    {
        return EnableSkipValue;
    }

    FString FRateModel::GetEnableSkipString() const
    {
        if (!EnableSkipValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableSkipValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FRateModel::GetSkipConsumeActions() const
    {
        return SkipConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FRateModel::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    TOptional<FString> FRateModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetRateNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRateModel> FRateModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRateModel>()
            ->WithRateModelId(Data->HasField("rateModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rateModelId", v))
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
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithTimingType(Data->HasField("timingType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("timingType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLockTime(Data->HasField("lockTime") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("lockTime", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEnableSkip(Data->HasField("enableSkip") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("enableSkip", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithSkipConsumeActions(Data->HasField("skipConsumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("skipConsumeActions") && Data->HasTypedField<EJson::Array>("skipConsumeActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("skipConsumeActions"))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>());
    }

    TSharedPtr<FJsonObject> FRateModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RateModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("rateModelId", RateModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
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
        if (TimingTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("timingType", TimingTypeValue.GetValue());
        }
        if (LockTimeValue.IsSet())
        {
            JsonRootObject->SetNumberField("lockTime", LockTimeValue.GetValue());
        }
        if (EnableSkipValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableSkip", EnableSkipValue.GetValue());
        }
        if (SkipConsumeActionsValue != nullptr && SkipConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SkipConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("skipConsumeActions", v);
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        return JsonRootObject;
    }

    FString FRateModel::TypeName = "RateModel";
}