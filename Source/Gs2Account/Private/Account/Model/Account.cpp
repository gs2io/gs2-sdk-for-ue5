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

#include "Account/Model/Account.h"

namespace Gs2::Account::Model
{
    FAccount::FAccount():
        AccountIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        TimeOffsetValue(TOptional<int32>()),
        BanStatusesValue(nullptr),
        BannedValue(TOptional<bool>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FAccount::FAccount(
        const FAccount& From
    ):
        AccountIdValue(From.AccountIdValue),
        UserIdValue(From.UserIdValue),
        PasswordValue(From.PasswordValue),
        TimeOffsetValue(From.TimeOffsetValue),
        BanStatusesValue(From.BanStatusesValue),
        BannedValue(From.BannedValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FAccount> FAccount::WithAccountId(
        const TOptional<FString> AccountId
    )
    {
        this->AccountIdValue = AccountId;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithTimeOffset(
        const TOptional<int32> TimeOffset
    )
    {
        this->TimeOffsetValue = TimeOffset;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithBanStatuses(
        const TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatuses
    )
    {
        this->BanStatusesValue = BanStatuses;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithBanned(
        const TOptional<bool> Banned
    )
    {
        this->BannedValue = Banned;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FAccount> FAccount::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FAccount::GetAccountId() const
    {
        return AccountIdValue;
    }
    TOptional<FString> FAccount::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FAccount::GetPassword() const
    {
        return PasswordValue;
    }
    TOptional<int32> FAccount::GetTimeOffset() const
    {
        return TimeOffsetValue;
    }

    FString FAccount::GetTimeOffsetString() const
    {
        if (!TimeOffsetValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TimeOffsetValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> FAccount::GetBanStatuses() const
    {
        return BanStatusesValue;
    }
    TOptional<bool> FAccount::GetBanned() const
    {
        return BannedValue;
    }

    FString FAccount::GetBannedString() const
    {
        if (!BannedValue.IsSet())
        {
            return FString("null");
        }
        return FString(BannedValue.GetValue() ? "true" : "false");
    }
    TOptional<int64> FAccount::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FAccount::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FAccount::GetRevision() const
    {
        return RevisionValue;
    }

    FString FAccount::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FAccount::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):account:(?<userId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAccount::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):account:(?<userId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAccount::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):account:(?<userId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAccount::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):account:(?<userId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FAccount> FAccount::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccount>()
            ->WithAccountId(Data->HasField("accountId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("accountId", v))
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
            ->WithPassword(Data->HasField("password") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("password", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTimeOffset(Data->HasField("timeOffset") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("timeOffset", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithBanStatuses(Data->HasField("banStatuses") ? [Data]() -> TSharedPtr<TArray<Model::FBanStatusPtr>>
                {
                    auto v = MakeShared<TArray<Model::FBanStatusPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("banStatuses") && Data->HasTypedField<EJson::Array>("banStatuses"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("banStatuses"))
                        {
                            v->Add(Model::FBanStatus::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBanStatusPtr>>())
            ->WithBanned(Data->HasField("banned") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("banned", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
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

    TSharedPtr<FJsonObject> FAccount::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AccountIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accountId", AccountIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        if (TimeOffsetValue.IsSet())
        {
            JsonRootObject->SetNumberField("timeOffset", TimeOffsetValue.GetValue());
        }
        if (BanStatusesValue != nullptr && BanStatusesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BanStatusesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("banStatuses", v);
        }
        if (BannedValue.IsSet())
        {
            JsonRootObject->SetBoolField("banned", BannedValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FAccount::TypeName = "Account";
}