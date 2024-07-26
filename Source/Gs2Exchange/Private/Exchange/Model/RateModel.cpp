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
        VerifyActionsValue(nullptr),
        ConsumeActionsValue(nullptr),
        TimingTypeValue(TOptional<FString>()),
        LockTimeValue(TOptional<int32>()),
        AcquireActionsValue(nullptr)
    {
    }

    FRateModel::FRateModel(
        const FRateModel& From
    ):
        RateModelIdValue(From.RateModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        VerifyActionsValue(From.VerifyActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        TimingTypeValue(From.TimingTypeValue),
        LockTimeValue(From.LockTimeValue),
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

    TSharedPtr<FRateModel> FRateModel::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
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
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FRateModel::GetVerifyActions() const
    {
        return VerifyActionsValue;
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
            ->WithRateModelId(Data->HasField(ANSI_TO_TCHAR("rateModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rateModelId"), v))
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
            ->WithVerifyActions(Data->HasField(ANSI_TO_TCHAR("verifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyActions")))
                        {
                            v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
            ->WithConsumeActions(Data->HasField(ANSI_TO_TCHAR("consumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeActions")))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithTimingType(Data->HasField(ANSI_TO_TCHAR("timingType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timingType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLockTime(Data->HasField(ANSI_TO_TCHAR("lockTime")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lockTime"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
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
        if (VerifyActionsValue != nullptr && VerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyActions", v);
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