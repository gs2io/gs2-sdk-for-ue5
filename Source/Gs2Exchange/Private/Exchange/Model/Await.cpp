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

#include "Exchange/Model/Await.h"

namespace Gs2::Exchange::Model
{
    FAwait::FAwait():
        AwaitIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        CountValue(TOptional<int32>()),
        ExchangedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FAwait::FAwait(
        const FAwait& From
    ):
        AwaitIdValue(From.AwaitIdValue),
        UserIdValue(From.UserIdValue),
        RateNameValue(From.RateNameValue),
        NameValue(From.NameValue),
        CountValue(From.CountValue),
        ExchangedAtValue(From.ExchangedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FAwait> FAwait::WithAwaitId(
        const TOptional<FString> AwaitId
    )
    {
        this->AwaitIdValue = AwaitId;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithExchangedAt(
        const TOptional<int64> ExchangedAt
    )
    {
        this->ExchangedAtValue = ExchangedAt;
        return SharedThis(this);
    }

    TSharedPtr<FAwait> FAwait::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FAwait::GetAwaitId() const
    {
        return AwaitIdValue;
    }
    TOptional<FString> FAwait::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FAwait::GetRateName() const
    {
        return RateNameValue;
    }
    TOptional<FString> FAwait::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FAwait::GetCount() const
    {
        return CountValue;
    }

    FString FAwait::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }
    TOptional<int64> FAwait::GetExchangedAt() const
    {
        return ExchangedAtValue;
    }

    FString FAwait::GetExchangedAtString() const
    {
        if (!ExchangedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExchangedAtValue.GetValue());
    }
    TOptional<int64> FAwait::GetRevision() const
    {
        return RevisionValue;
    }

    FString FAwait::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FAwait::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):user:(?<userId>.+):await:(?<awaitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAwait::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):user:(?<userId>.+):await:(?<awaitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAwait::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):user:(?<userId>.+):await:(?<awaitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAwait::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):user:(?<userId>.+):await:(?<awaitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAwait::GetAwaitNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):user:(?<userId>.+):await:(?<awaitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FAwait> FAwait::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAwait>()
            ->WithAwaitId(Data->HasField("awaitId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("awaitId", v))
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
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rateName", v))
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
            ->WithCount(Data->HasField("count") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("count", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithExchangedAt(Data->HasField("exchangedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("exchangedAt", v))
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

    TSharedPtr<FJsonObject> FAwait::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AwaitIdValue.IsSet())
        {
            JsonRootObject->SetStringField("awaitId", AwaitIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField("count", CountValue.GetValue());
        }
        if (ExchangedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("exchangedAt", FString::Printf(TEXT("%lld"), ExchangedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FAwait::TypeName = "Await";
}