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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FGooglePlaySetting final : public Gs2Object, public TSharedFromThis<FGooglePlaySetting>
    {
        TOptional<FString> PackageNameValue;
        TOptional<FString> PublicKeyValue;
        TOptional<FString> CredentialsJSONValue;

    public:
        FGooglePlaySetting();
        FGooglePlaySetting(
            const FGooglePlaySetting& From
        );
        virtual ~FGooglePlaySetting() override = default;

        TSharedPtr<FGooglePlaySetting> WithPackageName(const TOptional<FString> PackageName);
        TSharedPtr<FGooglePlaySetting> WithPublicKey(const TOptional<FString> PublicKey);
        TSharedPtr<FGooglePlaySetting> WithCredentialsJSON(const TOptional<FString> CredentialsJSON);

        TOptional<FString> GetPackageName() const;
        TOptional<FString> GetPublicKey() const;
        TOptional<FString> GetCredentialsJSON() const;


        static TSharedPtr<FGooglePlaySetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGooglePlaySetting, ESPMode::ThreadSafe> FGooglePlaySettingPtr;
}