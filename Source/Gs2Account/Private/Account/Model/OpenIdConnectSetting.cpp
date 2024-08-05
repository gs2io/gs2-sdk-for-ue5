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

#include "Account/Model/OpenIdConnectSetting.h"

namespace Gs2::Account::Model
{
    FOpenIdConnectSetting::FOpenIdConnectSetting():
        ConfigurationPathValue(TOptional<FString>()),
        ClientIdValue(TOptional<FString>()),
        ClientSecretValue(TOptional<FString>()),
        AppleTeamIdValue(TOptional<FString>()),
        AppleKeyIdValue(TOptional<FString>()),
        ApplePrivateKeyPemValue(TOptional<FString>())
    {
    }

    FOpenIdConnectSetting::FOpenIdConnectSetting(
        const FOpenIdConnectSetting& From
    ):
        ConfigurationPathValue(From.ConfigurationPathValue),
        ClientIdValue(From.ClientIdValue),
        ClientSecretValue(From.ClientSecretValue),
        AppleTeamIdValue(From.AppleTeamIdValue),
        AppleKeyIdValue(From.AppleKeyIdValue),
        ApplePrivateKeyPemValue(From.ApplePrivateKeyPemValue)
    {
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithConfigurationPath(
        const TOptional<FString> ConfigurationPath
    )
    {
        this->ConfigurationPathValue = ConfigurationPath;
        return SharedThis(this);
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithClientId(
        const TOptional<FString> ClientId
    )
    {
        this->ClientIdValue = ClientId;
        return SharedThis(this);
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithClientSecret(
        const TOptional<FString> ClientSecret
    )
    {
        this->ClientSecretValue = ClientSecret;
        return SharedThis(this);
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithAppleTeamId(
        const TOptional<FString> AppleTeamId
    )
    {
        this->AppleTeamIdValue = AppleTeamId;
        return SharedThis(this);
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithAppleKeyId(
        const TOptional<FString> AppleKeyId
    )
    {
        this->AppleKeyIdValue = AppleKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::WithApplePrivateKeyPem(
        const TOptional<FString> ApplePrivateKeyPem
    )
    {
        this->ApplePrivateKeyPemValue = ApplePrivateKeyPem;
        return SharedThis(this);
    }
    TOptional<FString> FOpenIdConnectSetting::GetConfigurationPath() const
    {
        return ConfigurationPathValue;
    }
    TOptional<FString> FOpenIdConnectSetting::GetClientId() const
    {
        return ClientIdValue;
    }
    TOptional<FString> FOpenIdConnectSetting::GetClientSecret() const
    {
        return ClientSecretValue;
    }
    TOptional<FString> FOpenIdConnectSetting::GetAppleTeamId() const
    {
        return AppleTeamIdValue;
    }
    TOptional<FString> FOpenIdConnectSetting::GetAppleKeyId() const
    {
        return AppleKeyIdValue;
    }
    TOptional<FString> FOpenIdConnectSetting::GetApplePrivateKeyPem() const
    {
        return ApplePrivateKeyPemValue;
    }

    TSharedPtr<FOpenIdConnectSetting> FOpenIdConnectSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FOpenIdConnectSetting>()
            ->WithConfigurationPath(Data->HasField(ANSI_TO_TCHAR("configurationPath")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("configurationPath"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithClientId(Data->HasField(ANSI_TO_TCHAR("clientId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clientId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithClientSecret(Data->HasField(ANSI_TO_TCHAR("clientSecret")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clientSecret"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAppleTeamId(Data->HasField(ANSI_TO_TCHAR("appleTeamId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("appleTeamId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAppleKeyId(Data->HasField(ANSI_TO_TCHAR("appleKeyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("appleKeyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithApplePrivateKeyPem(Data->HasField(ANSI_TO_TCHAR("applePrivateKeyPem")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("applePrivateKeyPem"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FOpenIdConnectSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ConfigurationPathValue.IsSet())
        {
            JsonRootObject->SetStringField("configurationPath", ConfigurationPathValue.GetValue());
        }
        if (ClientIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clientId", ClientIdValue.GetValue());
        }
        if (ClientSecretValue.IsSet())
        {
            JsonRootObject->SetStringField("clientSecret", ClientSecretValue.GetValue());
        }
        if (AppleTeamIdValue.IsSet())
        {
            JsonRootObject->SetStringField("appleTeamId", AppleTeamIdValue.GetValue());
        }
        if (AppleKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("appleKeyId", AppleKeyIdValue.GetValue());
        }
        if (ApplePrivateKeyPemValue.IsSet())
        {
            JsonRootObject->SetStringField("applePrivateKeyPem", ApplePrivateKeyPemValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FOpenIdConnectSetting::TypeName = "OpenIdConnectSetting";
}