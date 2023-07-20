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

#include "Enchant/Model/RarityParameterStatus.h"

namespace Gs2::Enchant::Model
{
    FRarityParameterStatus::FRarityParameterStatus():
        RarityParameterStatusIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ParameterValuesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FRarityParameterStatus::FRarityParameterStatus(
        const FRarityParameterStatus& From
    ):
        RarityParameterStatusIdValue(From.RarityParameterStatusIdValue),
        UserIdValue(From.UserIdValue),
        ParameterNameValue(From.ParameterNameValue),
        PropertyIdValue(From.PropertyIdValue),
        ParameterValuesValue(From.ParameterValuesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithRarityParameterStatusId(
        const TOptional<FString> RarityParameterStatusId
    )
    {
        this->RarityParameterStatusIdValue = RarityParameterStatusId;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FRarityParameterStatus::GetRarityParameterStatusId() const
    {
        return RarityParameterStatusIdValue;
    }
    TOptional<FString> FRarityParameterStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FRarityParameterStatus::GetParameterName() const
    {
        return ParameterNameValue;
    }
    TOptional<FString> FRarityParameterStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> FRarityParameterStatus::GetParameterValues() const
    {
        return ParameterValuesValue;
    }
    TOptional<int64> FRarityParameterStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRarityParameterStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRarityParameterStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRarityParameterStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FRarityParameterStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterStatus::GetParameterNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterStatus::GetPropertyIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):rarity:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRarityParameterStatus> FRarityParameterStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRarityParameterStatus>()
            ->WithRarityParameterStatusId(Data->HasField("rarityParameterStatusId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rarityParameterStatusId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("parameterName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("propertyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithParameterValues(Data->HasField("parameterValues") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterValuePtr>>
                {
                    auto v = MakeShared<TArray<Model::FRarityParameterValuePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("parameterValues") && Data->HasTypedField<EJson::Array>("parameterValues"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("parameterValues"))
                        {
                            v->Add(Model::FRarityParameterValue::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRarityParameterValuePtr>>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRarityParameterStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RarityParameterStatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField("rarityParameterStatusId", RarityParameterStatusIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ParameterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterName", ParameterNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (ParameterValuesValue != nullptr && ParameterValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParameterValuesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameterValues", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRarityParameterStatus::TypeName = "RarityParameterStatus";
}