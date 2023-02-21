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

#include "Version/Model/SignTargetVersion.h"

namespace Gs2::Version::Model
{
    FSignTargetVersion::FSignTargetVersion():
        RegionValue(TOptional<FString>()),
        NamespaceNameValue(TOptional<FString>()),
        VersionNameValue(TOptional<FString>()),
        VersionValue(nullptr)
    {
    }

    FSignTargetVersion::FSignTargetVersion(
        const FSignTargetVersion& From
    ):
        RegionValue(From.RegionValue),
        NamespaceNameValue(From.NamespaceNameValue),
        VersionNameValue(From.VersionNameValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FSignTargetVersion> FSignTargetVersion::WithRegion(
        const TOptional<FString> Region
    )
    {
        this->RegionValue = Region;
        return SharedThis(this);
    }

    TSharedPtr<FSignTargetVersion> FSignTargetVersion::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSignTargetVersion> FSignTargetVersion::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FSignTargetVersion> FSignTargetVersion::WithVersion(
        const TSharedPtr<FVersion> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }
    TOptional<FString> FSignTargetVersion::GetRegion() const
    {
        return RegionValue;
    }
    TOptional<FString> FSignTargetVersion::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }
    TOptional<FString> FSignTargetVersion::GetVersionName() const
    {
        return VersionNameValue;
    }
    TSharedPtr<FVersion> FSignTargetVersion::GetVersion() const
    {
        return VersionValue;
    }

    TSharedPtr<FSignTargetVersion> FSignTargetVersion::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSignTargetVersion>()
            ->WithRegion(Data->HasField("region") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("region", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVersionName(Data->HasField("versionName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("versionName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVersion(Data->HasField("version") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("version"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("version"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSignTargetVersion::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RegionValue.IsSet())
        {
            JsonRootObject->SetStringField("region", RegionValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (VersionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("versionName", VersionNameValue.GetValue());
        }
        if (VersionValue != nullptr && VersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("version", VersionValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FSignTargetVersion::TypeName = "SignTargetVersion";
}