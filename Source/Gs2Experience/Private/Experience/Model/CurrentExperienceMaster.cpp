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

#include "Experience/Model/CurrentExperienceMaster.h"

namespace Gs2::Experience::Model
{
    FCurrentExperienceMaster::FCurrentExperienceMaster():
        NamespaceIdValue(TOptional<FString>()),
        SettingsValue(TOptional<FString>())
    {
    }

    FCurrentExperienceMaster::FCurrentExperienceMaster(
        const FCurrentExperienceMaster& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        SettingsValue(From.SettingsValue)
    {
    }

    TSharedPtr<FCurrentExperienceMaster> FCurrentExperienceMaster::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FCurrentExperienceMaster> FCurrentExperienceMaster::WithSettings(
        const TOptional<FString> Settings
    )
    {
        this->SettingsValue = Settings;
        return SharedThis(this);
    }
    TOptional<FString> FCurrentExperienceMaster::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FCurrentExperienceMaster::GetSettings() const
    {
        return SettingsValue;
    }

    TOptional<FString> FCurrentExperienceMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCurrentExperienceMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCurrentExperienceMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCurrentExperienceMaster> FCurrentExperienceMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCurrentExperienceMaster>()
            ->WithNamespaceId(Data->HasField("namespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("namespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSettings(Data->HasField("settings") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("settings", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCurrentExperienceMaster::ToJson() const
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

    FString FCurrentExperienceMaster::TypeName = "CurrentExperienceMaster";
}