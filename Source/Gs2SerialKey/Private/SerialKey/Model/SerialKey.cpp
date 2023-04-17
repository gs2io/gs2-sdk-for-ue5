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

#include "SerialKey/Model/SerialKey.h"

namespace Gs2::SerialKey::Model
{
    FSerialKey::FSerialKey():
        SerialKeyIdValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        CodeValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        StatusValue(TOptional<FString>()),
        UsedUserIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UsedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FSerialKey::FSerialKey(
        const FSerialKey& From
    ):
        SerialKeyIdValue(From.SerialKeyIdValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        CodeValue(From.CodeValue),
        MetadataValue(From.MetadataValue),
        StatusValue(From.StatusValue),
        UsedUserIdValue(From.UsedUserIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UsedAtValue(From.UsedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FSerialKey> FSerialKey::WithSerialKeyId(
        const TOptional<FString> SerialKeyId
    )
    {
        this->SerialKeyIdValue = SerialKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithCode(
        const TOptional<FString> Code
    )
    {
        this->CodeValue = Code;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithUsedUserId(
        const TOptional<FString> UsedUserId
    )
    {
        this->UsedUserIdValue = UsedUserId;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithUsedAt(
        const TOptional<int64> UsedAt
    )
    {
        this->UsedAtValue = UsedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSerialKey> FSerialKey::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FSerialKey::GetSerialKeyId() const
    {
        return SerialKeyIdValue;
    }
    TOptional<FString> FSerialKey::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }
    TOptional<FString> FSerialKey::GetCode() const
    {
        return CodeValue;
    }
    TOptional<FString> FSerialKey::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FSerialKey::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<FString> FSerialKey::GetUsedUserId() const
    {
        return UsedUserIdValue;
    }
    TOptional<int64> FSerialKey::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSerialKey::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSerialKey::GetUsedAt() const
    {
        return UsedAtValue;
    }

    FString FSerialKey::GetUsedAtString() const
    {
        if (!UsedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UsedAtValue.GetValue());
    }
    TOptional<int64> FSerialKey::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FSerialKey::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FSerialKey::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):serialKey:(?<serialKeyCode>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSerialKey::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):serialKey:(?<serialKeyCode>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSerialKey::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):serialKey:(?<serialKeyCode>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSerialKey::GetSerialKeyCodeFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):serialKey:(?<namespaceName>.+):serialKey:(?<serialKeyCode>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSerialKey> FSerialKey::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSerialKey>()
            ->WithSerialKeyId(Data->HasField("serialKeyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("serialKeyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCampaignModelName(Data->HasField("campaignModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("campaignModelName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCode(Data->HasField("code") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("code", v))
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
            ->WithStatus(Data->HasField("status") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("status", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUsedUserId(Data->HasField("usedUserId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("usedUserId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUsedAt(Data->HasField("usedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("usedAt", v))
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

    TSharedPtr<FJsonObject> FSerialKey::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SerialKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("serialKeyId", SerialKeyIdValue.GetValue());
        }
        if (CampaignModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("campaignModelName", CampaignModelNameValue.GetValue());
        }
        if (CodeValue.IsSet())
        {
            JsonRootObject->SetStringField("code", CodeValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (UsedUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("usedUserId", UsedUserIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UsedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("usedAt", FString::Printf(TEXT("%lld"), UsedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSerialKey::TypeName = "SerialKey";
}