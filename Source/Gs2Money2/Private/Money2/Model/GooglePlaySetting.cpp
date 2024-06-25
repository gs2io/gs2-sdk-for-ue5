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

#include "Money2/Model/GooglePlaySetting.h"

namespace Gs2::Money2::Model
{
    FGooglePlaySetting::FGooglePlaySetting():
        PackageNameValue(TOptional<FString>()),
        PublicKeyValue(TOptional<FString>())
    {
    }

    FGooglePlaySetting::FGooglePlaySetting(
        const FGooglePlaySetting& From
    ):
        PackageNameValue(From.PackageNameValue),
        PublicKeyValue(From.PublicKeyValue)
    {
    }

    TSharedPtr<FGooglePlaySetting> FGooglePlaySetting::WithPackageName(
        const TOptional<FString> PackageName
    )
    {
        this->PackageNameValue = PackageName;
        return SharedThis(this);
    }

    TSharedPtr<FGooglePlaySetting> FGooglePlaySetting::WithPublicKey(
        const TOptional<FString> PublicKey
    )
    {
        this->PublicKeyValue = PublicKey;
        return SharedThis(this);
    }
    TOptional<FString> FGooglePlaySetting::GetPackageName() const
    {
        return PackageNameValue;
    }
    TOptional<FString> FGooglePlaySetting::GetPublicKey() const
    {
        return PublicKeyValue;
    }

    TSharedPtr<FGooglePlaySetting> FGooglePlaySetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGooglePlaySetting>()
            ->WithPackageName(Data->HasField(ANSI_TO_TCHAR("packageName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("packageName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPublicKey(Data->HasField(ANSI_TO_TCHAR("publicKey")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("publicKey"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGooglePlaySetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PackageNameValue.IsSet())
        {
            JsonRootObject->SetStringField("packageName", PackageNameValue.GetValue());
        }
        if (PublicKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("publicKey", PublicKeyValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGooglePlaySetting::TypeName = "GooglePlaySetting";
}