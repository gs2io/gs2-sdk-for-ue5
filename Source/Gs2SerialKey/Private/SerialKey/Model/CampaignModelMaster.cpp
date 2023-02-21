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

#include "SerialKey/Model/CampaignModelMaster.h"

namespace Gs2::SerialKey::Model
{
    FCampaignModelMaster::FCampaignModelMaster():
        CampaignIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        EnableCampaignCodeValue(TOptional<bool>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FCampaignModelMaster::FCampaignModelMaster(
        const FCampaignModelMaster& From
    ):
        CampaignIdValue(From.CampaignIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        EnableCampaignCodeValue(From.EnableCampaignCodeValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithCampaignId(
        const TOptional<FString> CampaignId
    )
    {
        this->CampaignIdValue = CampaignId;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithEnableCampaignCode(
        const TOptional<bool> EnableCampaignCode
    )
    {
        this->EnableCampaignCodeValue = EnableCampaignCode;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FCampaignModelMaster::GetCampaignId() const
    {
        return CampaignIdValue;
    }
    TOptional<FString> FCampaignModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FCampaignModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FCampaignModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<bool> FCampaignModelMaster::GetEnableCampaignCode() const
    {
        return EnableCampaignCodeValue;
    }

    FString FCampaignModelMaster::GetEnableCampaignCodeString() const
    {
        if (!EnableCampaignCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableCampaignCodeValue.GetValue() ? "true" : "false");
    }
    TOptional<int64> FCampaignModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FCampaignModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FCampaignModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FCampaignModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FCampaignModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModelMaster::GetCampaignModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCampaignModelMaster> FCampaignModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCampaignModelMaster>()
            ->WithCampaignId(Data->HasField("campaignId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("campaignId", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableCampaignCode(Data->HasField("enableCampaignCode") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("enableCampaignCode", v))
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

    TSharedPtr<FJsonObject> FCampaignModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CampaignIdValue.IsSet())
        {
            JsonRootObject->SetStringField("campaignId", CampaignIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (EnableCampaignCodeValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableCampaignCode", EnableCampaignCodeValue.GetValue());
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

    FString FCampaignModelMaster::TypeName = "CampaignModelMaster";
}