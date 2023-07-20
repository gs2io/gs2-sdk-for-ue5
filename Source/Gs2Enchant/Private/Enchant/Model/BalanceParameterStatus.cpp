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

#include "Enchant/Model/BalanceParameterStatus.h"

namespace Gs2::Enchant::Model
{
    FBalanceParameterStatus::FBalanceParameterStatus():
        BalanceParameterStatusIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ParameterValuesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FBalanceParameterStatus::FBalanceParameterStatus(
        const FBalanceParameterStatus& From
    ):
        BalanceParameterStatusIdValue(From.BalanceParameterStatusIdValue),
        UserIdValue(From.UserIdValue),
        ParameterNameValue(From.ParameterNameValue),
        PropertyIdValue(From.PropertyIdValue),
        ParameterValuesValue(From.ParameterValuesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithBalanceParameterStatusId(
        const TOptional<FString> BalanceParameterStatusId
    )
    {
        this->BalanceParameterStatusIdValue = BalanceParameterStatusId;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FBalanceParameterStatus::GetBalanceParameterStatusId() const
    {
        return BalanceParameterStatusIdValue;
    }
    TOptional<FString> FBalanceParameterStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FBalanceParameterStatus::GetParameterName() const
    {
        return ParameterNameValue;
    }
    TOptional<FString> FBalanceParameterStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> FBalanceParameterStatus::GetParameterValues() const
    {
        return ParameterValuesValue;
    }
    TOptional<int64> FBalanceParameterStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FBalanceParameterStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FBalanceParameterStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FBalanceParameterStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FBalanceParameterStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBalanceParameterStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBalanceParameterStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBalanceParameterStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBalanceParameterStatus::GetParameterNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBalanceParameterStatus::GetPropertyIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):user:(?<userId>.+):balance:(?<parameterName>.+):(?<propertyId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBalanceParameterStatus> FBalanceParameterStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBalanceParameterStatus>()
            ->WithBalanceParameterStatusId(Data->HasField("balanceParameterStatusId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("balanceParameterStatusId", v))
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
            ->WithParameterValues(Data->HasField("parameterValues") ? [Data]() -> TSharedPtr<TArray<Model::FBalanceParameterValuePtr>>
                {
                    auto v = MakeShared<TArray<Model::FBalanceParameterValuePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("parameterValues") && Data->HasTypedField<EJson::Array>("parameterValues"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("parameterValues"))
                        {
                            v->Add(Model::FBalanceParameterValue::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBalanceParameterValuePtr>>())
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

    TSharedPtr<FJsonObject> FBalanceParameterStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BalanceParameterStatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField("balanceParameterStatusId", BalanceParameterStatusIdValue.GetValue());
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

    FString FBalanceParameterStatus::TypeName = "BalanceParameterStatus";
}