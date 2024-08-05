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

#include "Account/Model/TakeOverTypeModel.h"

namespace Gs2::Account::Model
{
    FTakeOverTypeModel::FTakeOverTypeModel():
        TakeOverTypeModelIdValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        MetadataValue(TOptional<FString>()),
        OpenIdConnectSettingValue(nullptr)
    {
    }

    FTakeOverTypeModel::FTakeOverTypeModel(
        const FTakeOverTypeModel& From
    ):
        TakeOverTypeModelIdValue(From.TakeOverTypeModelIdValue),
        TypeValue(From.TypeValue),
        MetadataValue(From.MetadataValue),
        OpenIdConnectSettingValue(From.OpenIdConnectSettingValue)
    {
    }

    TSharedPtr<FTakeOverTypeModel> FTakeOverTypeModel::WithTakeOverTypeModelId(
        const TOptional<FString> TakeOverTypeModelId
    )
    {
        this->TakeOverTypeModelIdValue = TakeOverTypeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModel> FTakeOverTypeModel::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModel> FTakeOverTypeModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FTakeOverTypeModel> FTakeOverTypeModel::WithOpenIdConnectSetting(
        const TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSetting
    )
    {
        this->OpenIdConnectSettingValue = OpenIdConnectSetting;
        return SharedThis(this);
    }
    TOptional<FString> FTakeOverTypeModel::GetTakeOverTypeModelId() const
    {
        return TakeOverTypeModelIdValue;
    }
    TOptional<int32> FTakeOverTypeModel::GetType() const
    {
        return TypeValue;
    }

    FString FTakeOverTypeModel::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }
    TOptional<FString> FTakeOverTypeModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<FOpenIdConnectSetting> FTakeOverTypeModel::GetOpenIdConnectSetting() const
    {
        return OpenIdConnectSettingValue;
    }

    TOptional<FString> FTakeOverTypeModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FTakeOverTypeModel::GetTypeFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+):model:takeOver:(?<type>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FTakeOverTypeModel> FTakeOverTypeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTakeOverTypeModel>()
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
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FTakeOverTypeModel::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (OpenIdConnectSettingValue != nullptr && OpenIdConnectSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("openIdConnectSetting", OpenIdConnectSettingValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FTakeOverTypeModel::TypeName = "TakeOverTypeModel";
}