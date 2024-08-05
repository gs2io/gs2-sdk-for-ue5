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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FOpenIdConnectSetting final : public Gs2Object, public TSharedFromThis<FOpenIdConnectSetting>
    {
        TOptional<FString> ConfigurationPathValue;
        TOptional<FString> ClientIdValue;
        TOptional<FString> ClientSecretValue;
        TOptional<FString> AppleTeamIdValue;
        TOptional<FString> AppleKeyIdValue;
        TOptional<FString> ApplePrivateKeyPemValue;

    public:
        FOpenIdConnectSetting();
        FOpenIdConnectSetting(
            const FOpenIdConnectSetting& From
        );
        virtual ~FOpenIdConnectSetting() override = default;

        TSharedPtr<FOpenIdConnectSetting> WithConfigurationPath(const TOptional<FString> ConfigurationPath);
        TSharedPtr<FOpenIdConnectSetting> WithClientId(const TOptional<FString> ClientId);
        TSharedPtr<FOpenIdConnectSetting> WithClientSecret(const TOptional<FString> ClientSecret);
        TSharedPtr<FOpenIdConnectSetting> WithAppleTeamId(const TOptional<FString> AppleTeamId);
        TSharedPtr<FOpenIdConnectSetting> WithAppleKeyId(const TOptional<FString> AppleKeyId);
        TSharedPtr<FOpenIdConnectSetting> WithApplePrivateKeyPem(const TOptional<FString> ApplePrivateKeyPem);

        TOptional<FString> GetConfigurationPath() const;
        TOptional<FString> GetClientId() const;
        TOptional<FString> GetClientSecret() const;
        TOptional<FString> GetAppleTeamId() const;
        TOptional<FString> GetAppleKeyId() const;
        TOptional<FString> GetApplePrivateKeyPem() const;


        static TSharedPtr<FOpenIdConnectSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FOpenIdConnectSetting, ESPMode::ThreadSafe> FOpenIdConnectSettingPtr;
}