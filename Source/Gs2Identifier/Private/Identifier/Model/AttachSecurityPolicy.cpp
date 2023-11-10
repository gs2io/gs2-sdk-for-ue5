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

#include "Identifier/Model/AttachSecurityPolicy.h"

namespace Gs2::Identifier::Model
{
    FAttachSecurityPolicy::FAttachSecurityPolicy():
        UserIdValue(TOptional<FString>()),
        SecurityPolicyIdsValue(nullptr),
        AttachedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FAttachSecurityPolicy::FAttachSecurityPolicy(
        const FAttachSecurityPolicy& From
    ):
        UserIdValue(From.UserIdValue),
        SecurityPolicyIdsValue(From.SecurityPolicyIdsValue),
        AttachedAtValue(From.AttachedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithSecurityPolicyIds(
        const TSharedPtr<TArray<FString>> SecurityPolicyIds
    )
    {
        this->SecurityPolicyIdsValue = SecurityPolicyIds;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithAttachedAt(
        const TOptional<int64> AttachedAt
    )
    {
        this->AttachedAtValue = AttachedAt;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FAttachSecurityPolicy::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<FString>> FAttachSecurityPolicy::GetSecurityPolicyIds() const
    {
        return SecurityPolicyIdsValue;
    }
    TOptional<int64> FAttachSecurityPolicy::GetAttachedAt() const
    {
        return AttachedAtValue;
    }

    FString FAttachSecurityPolicy::GetAttachedAtString() const
    {
        if (!AttachedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AttachedAtValue.GetValue());
    }
    TOptional<int64> FAttachSecurityPolicy::GetRevision() const
    {
        return RevisionValue;
    }

    FString FAttachSecurityPolicy::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FAttachSecurityPolicy::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAttachSecurityPolicy::GetUserNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2::(?<ownerId>.+):identifier:user:(?<userName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FAttachSecurityPolicy> FAttachSecurityPolicy::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttachSecurityPolicy>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSecurityPolicyIds(Data->HasField("securityPolicyIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("securityPolicyIds") && Data->HasTypedField<EJson::Array>("securityPolicyIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("securityPolicyIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithAttachedAt(Data->HasField("attachedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("attachedAt", v))
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

    TSharedPtr<FJsonObject> FAttachSecurityPolicy::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (SecurityPolicyIdsValue != nullptr && SecurityPolicyIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SecurityPolicyIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("securityPolicyIds", v);
        }
        if (AttachedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("attachedAt", FString::Printf(TEXT("%lld"), AttachedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FAttachSecurityPolicy::TypeName = "AttachSecurityPolicy";
}