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

#include "Version/Model/TargetVersion.h"

namespace Gs2::Version::Model
{
    FTargetVersion::FTargetVersion():
        VersionNameValue(TOptional<FString>()),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        VersionValue(nullptr)
    {
    }

    FTargetVersion::FTargetVersion(
        const FTargetVersion& From
    ):
        VersionNameValue(From.VersionNameValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FTargetVersion> FTargetVersion::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FTargetVersion> FTargetVersion::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FTargetVersion> FTargetVersion::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FTargetVersion> FTargetVersion::WithVersion(
        const TSharedPtr<FVersion> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }
    TOptional<FString> FTargetVersion::GetVersionName() const
    {
        return VersionNameValue;
    }
    TOptional<FString> FTargetVersion::GetBody() const
    {
        return BodyValue;
    }
    TOptional<FString> FTargetVersion::GetSignature() const
    {
        return SignatureValue;
    }
    TSharedPtr<FVersion> FTargetVersion::GetVersion() const
    {
        return VersionValue;
    }

    TSharedPtr<FTargetVersion> FTargetVersion::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTargetVersion>()
            ->WithVersionName(Data->HasField(ANSI_TO_TCHAR("versionName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("versionName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBody(Data->HasField(ANSI_TO_TCHAR("body")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("body"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField(ANSI_TO_TCHAR("signature")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signature"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVersion(Data->HasField(ANSI_TO_TCHAR("version")) ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("version")))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("version")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FTargetVersion::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (VersionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("versionName", VersionNameValue.GetValue());
        }
        if (BodyValue.IsSet())
        {
            JsonRootObject->SetStringField("body", BodyValue.GetValue());
        }
        if (SignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signature", SignatureValue.GetValue());
        }
        if (VersionValue != nullptr && VersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("version", VersionValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FTargetVersion::TypeName = "TargetVersion";
}