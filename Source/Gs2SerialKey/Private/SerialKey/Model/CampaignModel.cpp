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

#include "SerialKey/Model/CampaignModel.h"

namespace Gs2::SerialKey::Model
{
    FCampaignModel::FCampaignModel():
        CampaignIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        EnableCampaignCodeValue(TOptional<bool>())
    {
    }

    FCampaignModel::FCampaignModel(
        const FCampaignModel& From
    ):
        CampaignIdValue(From.CampaignIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        EnableCampaignCodeValue(From.EnableCampaignCodeValue)
    {
    }

    TSharedPtr<FCampaignModel> FCampaignModel::WithCampaignId(
        const TOptional<FString> CampaignId
    )
    {
        this->CampaignIdValue = CampaignId;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModel> FCampaignModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModel> FCampaignModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCampaignModel> FCampaignModel::WithEnableCampaignCode(
        const TOptional<bool> EnableCampaignCode
    )
    {
        this->EnableCampaignCodeValue = EnableCampaignCode;
        return SharedThis(this);
    }
    TOptional<FString> FCampaignModel::GetCampaignId() const
    {
        return CampaignIdValue;
    }
    TOptional<FString> FCampaignModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FCampaignModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<bool> FCampaignModel::GetEnableCampaignCode() const
    {
        return EnableCampaignCodeValue;
    }

    FString FCampaignModel::GetEnableCampaignCodeString() const
    {
        if (!EnableCampaignCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableCampaignCodeValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FCampaignModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCampaignModel::GetCampaignModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):master:campaign:(?<campaignModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCampaignModel> FCampaignModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCampaignModel>()
            ->WithCampaignId(Data->HasField("campaignId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("campaignId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
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
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FCampaignModel::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (EnableCampaignCodeValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableCampaignCode", EnableCampaignCodeValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FCampaignModel::TypeName = "CampaignModel";
}