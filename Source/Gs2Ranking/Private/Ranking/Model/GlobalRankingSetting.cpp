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

#include "Ranking/Model/GlobalRankingSetting.h"

namespace Gs2::Ranking::Model
{
    FGlobalRankingSetting::FGlobalRankingSetting():
        UniqueByUserIdValue(TOptional<bool>()),
        CalculateIntervalMinutesValue(TOptional<int32>()),
        CalculateFixedTimingValue(nullptr),
        AdditionalScopesValue(nullptr),
        IgnoreUserIdsValue(nullptr),
        GenerationValue(TOptional<FString>())
    {
    }

    FGlobalRankingSetting::FGlobalRankingSetting(
        const FGlobalRankingSetting& From
    ):
        UniqueByUserIdValue(From.UniqueByUserIdValue),
        CalculateIntervalMinutesValue(From.CalculateIntervalMinutesValue),
        CalculateFixedTimingValue(From.CalculateFixedTimingValue),
        AdditionalScopesValue(From.AdditionalScopesValue),
        IgnoreUserIdsValue(From.IgnoreUserIdsValue),
        GenerationValue(From.GenerationValue)
    {
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithUniqueByUserId(
        const TOptional<bool> UniqueByUserId
    )
    {
        this->UniqueByUserIdValue = UniqueByUserId;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithCalculateIntervalMinutes(
        const TOptional<int32> CalculateIntervalMinutes
    )
    {
        this->CalculateIntervalMinutesValue = CalculateIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithCalculateFixedTiming(
        const TSharedPtr<FFixedTiming> CalculateFixedTiming
    )
    {
        this->CalculateFixedTimingValue = CalculateFixedTiming;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithAdditionalScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> AdditionalScopes
    )
    {
        this->AdditionalScopesValue = AdditionalScopes;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithIgnoreUserIds(
        const TSharedPtr<TArray<FString>> IgnoreUserIds
    )
    {
        this->IgnoreUserIdsValue = IgnoreUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }
    TOptional<bool> FGlobalRankingSetting::GetUniqueByUserId() const
    {
        return UniqueByUserIdValue;
    }

    FString FGlobalRankingSetting::GetUniqueByUserIdString() const
    {
        if (!UniqueByUserIdValue.IsSet())
        {
            return FString("null");
        }
        return FString(UniqueByUserIdValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FGlobalRankingSetting::GetCalculateIntervalMinutes() const
    {
        return CalculateIntervalMinutesValue;
    }

    FString FGlobalRankingSetting::GetCalculateIntervalMinutesString() const
    {
        if (!CalculateIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateIntervalMinutesValue.GetValue());
    }
    TSharedPtr<FFixedTiming> FGlobalRankingSetting::GetCalculateFixedTiming() const
    {
        return CalculateFixedTimingValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FScope>>> FGlobalRankingSetting::GetAdditionalScopes() const
    {
        return AdditionalScopesValue;
    }
    TSharedPtr<TArray<FString>> FGlobalRankingSetting::GetIgnoreUserIds() const
    {
        return IgnoreUserIdsValue;
    }
    TOptional<FString> FGlobalRankingSetting::GetGeneration() const
    {
        return GenerationValue;
    }

    TSharedPtr<FGlobalRankingSetting> FGlobalRankingSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGlobalRankingSetting>()
            ->WithUniqueByUserId(Data->HasField(ANSI_TO_TCHAR("uniqueByUserId")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("uniqueByUserId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCalculateIntervalMinutes(Data->HasField(ANSI_TO_TCHAR("calculateIntervalMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateIntervalMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCalculateFixedTiming(Data->HasField(ANSI_TO_TCHAR("calculateFixedTiming")) ? [Data]() -> Model::FFixedTimingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("calculateFixedTiming")))
                    {
                        return nullptr;
                    }
                    return Model::FFixedTiming::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("calculateFixedTiming")));
                 }() : nullptr)
            ->WithAdditionalScopes(Data->HasField(ANSI_TO_TCHAR("additionalScopes")) ? [Data]() -> TSharedPtr<TArray<Model::FScopePtr>>
                {
                    auto v = MakeShared<TArray<Model::FScopePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("additionalScopes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("additionalScopes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("additionalScopes")))
                        {
                            v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FScopePtr>>())
            ->WithIgnoreUserIds(Data->HasField(ANSI_TO_TCHAR("ignoreUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("ignoreUserIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("ignoreUserIds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("ignoreUserIds")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithGeneration(Data->HasField(ANSI_TO_TCHAR("generation")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("generation"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGlobalRankingSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UniqueByUserIdValue.IsSet())
        {
            JsonRootObject->SetBoolField("uniqueByUserId", UniqueByUserIdValue.GetValue());
        }
        if (CalculateIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateIntervalMinutes", CalculateIntervalMinutesValue.GetValue());
        }
        if (CalculateFixedTimingValue != nullptr && CalculateFixedTimingValue.IsValid())
        {
            JsonRootObject->SetObjectField("calculateFixedTiming", CalculateFixedTimingValue->ToJson());
        }
        if (AdditionalScopesValue != nullptr && AdditionalScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AdditionalScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("additionalScopes", v);
        }
        if (IgnoreUserIdsValue != nullptr && IgnoreUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *IgnoreUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("ignoreUserIds", v);
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGlobalRankingSetting::TypeName = "GlobalRankingSetting";
}