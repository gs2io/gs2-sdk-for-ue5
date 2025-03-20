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
    class GS2MONEY2_API FAppleAppStoreSetting final : public FGs2Object, public TSharedFromThis<FAppleAppStoreSetting>
    {
        TOptional<FString> BundleIdValue;
        TOptional<FString> SharedSecretKeyValue;
        TOptional<FString> IssuerIdValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> PrivateKeyPemValue;

    public:
        FAppleAppStoreSetting();
        FAppleAppStoreSetting(
            const FAppleAppStoreSetting& From
        );
        virtual ~FAppleAppStoreSetting() override = default;

        TSharedPtr<FAppleAppStoreSetting> WithBundleId(const TOptional<FString> BundleId);
        TSharedPtr<FAppleAppStoreSetting> WithSharedSecretKey(const TOptional<FString> SharedSecretKey);
        TSharedPtr<FAppleAppStoreSetting> WithIssuerId(const TOptional<FString> IssuerId);
        TSharedPtr<FAppleAppStoreSetting> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FAppleAppStoreSetting> WithPrivateKeyPem(const TOptional<FString> PrivateKeyPem);

        TOptional<FString> GetBundleId() const;
        TOptional<FString> GetSharedSecretKey() const;
        TOptional<FString> GetIssuerId() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetPrivateKeyPem() const;


        static TSharedPtr<FAppleAppStoreSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAppleAppStoreSetting, ESPMode::ThreadSafe> FAppleAppStoreSettingPtr;
}