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

#include "Stamina/Model/Stamina.h"

namespace Gs2::Stamina::Model
{
    FStamina::FStamina():
        StaminaIdValue(TOptional<FString>()),
        StaminaNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ValueValue(TOptional<int32>()),
        MaxValueValue(TOptional<int32>()),
        RecoverIntervalMinutesValue(TOptional<int32>()),
        RecoverValueValue(TOptional<int32>()),
        OverflowValueValue(TOptional<int32>()),
        NextRecoverAtValue(TOptional<int64>()),
        LastRecoveredAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStamina::FStamina(
        const FStamina& From
    ):
        StaminaIdValue(From.StaminaIdValue),
        StaminaNameValue(From.StaminaNameValue),
        UserIdValue(From.UserIdValue),
        ValueValue(From.ValueValue),
        MaxValueValue(From.MaxValueValue),
        RecoverIntervalMinutesValue(From.RecoverIntervalMinutesValue),
        RecoverValueValue(From.RecoverValueValue),
        OverflowValueValue(From.OverflowValueValue),
        NextRecoverAtValue(From.NextRecoverAtValue),
        LastRecoveredAtValue(From.LastRecoveredAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStamina> FStamina::WithStaminaId(
        const TOptional<FString> StaminaId
    )
    {
        this->StaminaIdValue = StaminaId;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithStaminaName(
        const TOptional<FString> StaminaName
    )
    {
        this->StaminaNameValue = StaminaName;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithMaxValue(
        const TOptional<int32> MaxValue
    )
    {
        this->MaxValueValue = MaxValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithOverflowValue(
        const TOptional<int32> OverflowValue
    )
    {
        this->OverflowValueValue = OverflowValue;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithNextRecoverAt(
        const TOptional<int64> NextRecoverAt
    )
    {
        this->NextRecoverAtValue = NextRecoverAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithLastRecoveredAt(
        const TOptional<int64> LastRecoveredAt
    )
    {
        this->LastRecoveredAtValue = LastRecoveredAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStamina> FStamina::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStamina::GetStaminaId() const
    {
        return StaminaIdValue;
    }
    TOptional<FString> FStamina::GetStaminaName() const
    {
        return StaminaNameValue;
    }
    TOptional<FString> FStamina::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FStamina::GetValue() const
    {
        return ValueValue;
    }

    FString FStamina::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetMaxValue() const
    {
        return MaxValueValue;
    }

    FString FStamina::GetMaxValueString() const
    {
        if (!MaxValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FStamina::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FStamina::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FStamina::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FStamina::GetOverflowValue() const
    {
        return OverflowValueValue;
    }

    FString FStamina::GetOverflowValueString() const
    {
        if (!OverflowValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), OverflowValueValue.GetValue());
    }
    TOptional<int64> FStamina::GetNextRecoverAt() const
    {
        return NextRecoverAtValue;
    }

    FString FStamina::GetNextRecoverAtString() const
    {
        if (!NextRecoverAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRecoverAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetLastRecoveredAt() const
    {
        return LastRecoveredAtValue;
    }

    FString FStamina::GetLastRecoveredAtString() const
    {
        if (!LastRecoveredAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastRecoveredAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStamina::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStamina::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStamina::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStamina::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStamina::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStamina::GetStaminaNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):user:(?<userId>.+):stamina:(?<staminaName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStamina> FStamina::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStamina>()
            ->WithStaminaId(Data->HasField("staminaId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("staminaId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStaminaName(Data->HasField("staminaName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("staminaName", v))
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
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("value", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxValue(Data->HasField("maxValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maxValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecoverIntervalMinutes(Data->HasField("recoverIntervalMinutes") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("recoverIntervalMinutes", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecoverValue(Data->HasField("recoverValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("recoverValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithOverflowValue(Data->HasField("overflowValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("overflowValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithNextRecoverAt(Data->HasField("nextRecoverAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("nextRecoverAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastRecoveredAt(Data->HasField("lastRecoveredAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("lastRecoveredAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FStamina::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StaminaIdValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaId", StaminaIdValue.GetValue());
        }
        if (StaminaNameValue.IsSet())
        {
            JsonRootObject->SetStringField("staminaName", StaminaNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        if (MaxValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxValue", MaxValueValue.GetValue());
        }
        if (RecoverIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverIntervalMinutes", RecoverIntervalMinutesValue.GetValue());
        }
        if (RecoverValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("recoverValue", RecoverValueValue.GetValue());
        }
        if (OverflowValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("overflowValue", OverflowValueValue.GetValue());
        }
        if (NextRecoverAtValue.IsSet())
        {
            JsonRootObject->SetStringField("nextRecoverAt", FString::Printf(TEXT("%lld"), NextRecoverAtValue.GetValue()));
        }
        if (LastRecoveredAtValue.IsSet())
        {
            JsonRootObject->SetStringField("lastRecoveredAt", FString::Printf(TEXT("%lld"), LastRecoveredAtValue.GetValue()));
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

    FString FStamina::TypeName = "Stamina";
}