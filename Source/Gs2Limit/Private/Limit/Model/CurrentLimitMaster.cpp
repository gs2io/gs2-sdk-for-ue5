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

#include "Limit/Model/CurrentLimitMaster.h"

namespace Gs2::Limit::Model
{
    FCurrentLimitMaster::FCurrentLimitMaster():
        NamespaceIdValue(TOptional<FString>()),
        SettingsValue(TOptional<FString>())
    {
    }

    FCurrentLimitMaster::FCurrentLimitMaster(
        const FCurrentLimitMaster& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        SettingsValue(From.SettingsValue)
    {
    }

    TSharedPtr<FCurrentLimitMaster> FCurrentLimitMaster::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FCurrentLimitMaster> FCurrentLimitMaster::WithSettings(
        const TOptional<FString> Settings
    )
    {
        this->SettingsValue = Settings;
        return SharedThis(this);
    }
    TOptional<FString> FCurrentLimitMaster::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FCurrentLimitMaster::GetSettings() const
    {
        return SettingsValue;
    }

    TOptional<FString> FCurrentLimitMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCurrentLimitMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCurrentLimitMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCurrentLimitMaster> FCurrentLimitMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCurrentLimitMaster>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSettings(Data->HasField(ANSI_TO_TCHAR("settings")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("settings"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCurrentLimitMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (SettingsValue.IsSet())
        {
            JsonRootObject->SetStringField("settings", SettingsValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FCurrentLimitMaster::TypeName = "CurrentLimitMaster";
}