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

#include "Mission/Model/Counter.h"

namespace Gs2::Mission::Model
{
    FCounter::FCounter():
        CounterIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        ValuesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FCounter::FCounter(
        const FCounter& From
    ):
        CounterIdValue(From.CounterIdValue),
        UserIdValue(From.UserIdValue),
        NameValue(From.NameValue),
        ValuesValue(From.ValuesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FCounter> FCounter::WithCounterId(
        const TOptional<FString> CounterId
    )
    {
        this->CounterIdValue = CounterId;
        return SharedThis(this);
    }

    TSharedPtr<FCounter> FCounter::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCounter> FCounter::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCounter> FCounter::WithValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }

    TSharedPtr<FCounter> FCounter::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FCounter> FCounter::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FCounter::GetCounterId() const
    {
        return CounterIdValue;
    }
    TOptional<FString> FCounter::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FCounter::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> FCounter::GetValues() const
    {
        return ValuesValue;
    }
    TOptional<int64> FCounter::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FCounter::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FCounter::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FCounter::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FCounter::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):counter:(?<counterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCounter::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):counter:(?<counterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCounter::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):counter:(?<counterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCounter::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):counter:(?<counterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCounter::GetCounterNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):counter:(?<counterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCounter> FCounter::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCounter>()
            ->WithCounterId(Data->HasField("counterId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("counterId", v))
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValues(Data->HasField("values") ? [Data]() -> TSharedPtr<TArray<Model::FScopedValuePtr>>
                {
                    auto v = MakeShared<TArray<Model::FScopedValuePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("values") && Data->HasTypedField<EJson::Array>("values"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("values"))
                        {
                            v->Add(Model::FScopedValue::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FCounter::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CounterIdValue.IsSet())
        {
            JsonRootObject->SetStringField("counterId", CounterIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("values", v);
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

    FString FCounter::TypeName = "Counter";
}