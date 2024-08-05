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

#include "Account/Model/TakeOverTypeModelMaster.h"

namespace Gs2::Account::Model
{
    FTakeOverTypeModelMaster::FTakeOverTypeModelMaster():
        TakeOverTypeModelIdValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        OpenIdConnectSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FTakeOverTypeModelMaster::FTakeOverTypeModelMaster(
        const FTakeOverTypeModelMaster& From
    ):
        TakeOverTypeModelIdValue(From.TakeOverTypeModelIdValue),
        TypeValue(From.TypeValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        OpenIdConnectSettingValue(From.OpenIdConnectSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithTakeOverTypeModelId(
        const TOptional<FString> TakeOverTypeModelId
    )
    {
        this->TakeOverTypeModelIdValue = TakeOverTypeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithOpenIdConnectSetting(
        const TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSetting
    )
    {
        this->OpenIdConnectSettingValue = OpenIdConnectSetting;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FTakeOverTypeModelMaster::GetTakeOverTypeModelId() const
    {
        return TakeOverTypeModelIdValue;
    }
    TOptional<int32> FTakeOverTypeModelMaster::GetType() const
    {
        return TypeValue;
    }

    FString FTakeOverTypeModelMaster::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FTakeOverTypeModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FTakeOverTypeModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<FOpenIdConnectSetting> FTakeOverTypeModelMaster::GetOpenIdConnectSetting() const
    {
        return OpenIdConnectSettingValue;
    }
    TOptional<int64> FTakeOverTypeModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FTakeOverTypeModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FTakeOverTypeModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FTakeOverTypeModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FTakeOverTypeModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FTakeOverTypeModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FTakeOverTypeModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModelMaster::GetTypeFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FTakeOverTypeModelMaster> FTakeOverTypeModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTakeOverTypeModelMaster>()
            ->WithTakeOverTypeModelId(Data->HasField(ANSI_TO_TCHAR("takeOverTypeModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("takeOverTypeModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithOpenIdConnectSetting(Data->HasField(ANSI_TO_TCHAR("openIdConnectSetting")) ? [Data]() -> Model::FOpenIdConnectSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("openIdConnectSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FOpenIdConnectSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("openIdConnectSetting")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FTakeOverTypeModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TakeOverTypeModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("takeOverTypeModelId", TakeOverTypeModelIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (OpenIdConnectSettingValue != nullptr && OpenIdConnectSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("openIdConnectSetting", OpenIdConnectSettingValue->ToJson());
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

    FString FTakeOverTypeModelMaster::TypeName = "TakeOverTypeModelMaster";
}