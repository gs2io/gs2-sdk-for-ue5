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

#include "Dictionary/Model/Entry.h"

namespace Gs2::Dictionary::Model
{
    FEntry::FEntry():
        EntryIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        AcquiredAtValue(TOptional<int64>())
    {
    }

    FEntry::FEntry(
        const FEntry& From
    ):
        EntryIdValue(From.EntryIdValue),
        UserIdValue(From.UserIdValue),
        NameValue(From.NameValue),
        AcquiredAtValue(From.AcquiredAtValue)
    {
    }

    TSharedPtr<FEntry> FEntry::WithEntryId(
        const TOptional<FString> EntryId
    )
    {
        this->EntryIdValue = EntryId;
        return SharedThis(this);
    }

    TSharedPtr<FEntry> FEntry::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEntry> FEntry::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEntry> FEntry::WithAcquiredAt(
        const TOptional<int64> AcquiredAt
    )
    {
        this->AcquiredAtValue = AcquiredAt;
        return SharedThis(this);
    }
    TOptional<FString> FEntry::GetEntryId() const
    {
        return EntryIdValue;
    }
    TOptional<FString> FEntry::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEntry::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FEntry::GetAcquiredAt() const
    {
        return AcquiredAtValue;
    }

    FString FEntry::GetAcquiredAtString() const
    {
        if (!AcquiredAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AcquiredAtValue.GetValue());
    }

    TOptional<FString> FEntry::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):dictionary:(?<namespaceName>.+):user:(?<userId>.+):entry:(?<entryModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEntry::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):dictionary:(?<namespaceName>.+):user:(?<userId>.+):entry:(?<entryModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEntry::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):dictionary:(?<namespaceName>.+):user:(?<userId>.+):entry:(?<entryModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEntry::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):dictionary:(?<namespaceName>.+):user:(?<userId>.+):entry:(?<entryModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEntry::GetEntryModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):dictionary:(?<namespaceName>.+):user:(?<userId>.+):entry:(?<entryModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FEntry> FEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEntry>()
            ->WithEntryId(Data->HasField("entryId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("entryId", v))
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
            ->WithAcquiredAt(Data->HasField("acquiredAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("acquiredAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EntryIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryId", EntryIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (AcquiredAtValue.IsSet())
        {
            JsonRootObject->SetStringField("acquiredAt", FString::Printf(TEXT("%lld"), AcquiredAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FEntry::TypeName = "Entry";
}