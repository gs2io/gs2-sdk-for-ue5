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
    class GS2MONEY2_API FAppleAppStoreSetting final : public Gs2Object, public TSharedFromThis<FAppleAppStoreSetting>
    {
        TOptional<FString> BundleIdValue;
        TOptional<FString> TeamIdValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> PrivateKeyPemValue;

    public:
        FAppleAppStoreSetting();
        FAppleAppStoreSetting(
            const FAppleAppStoreSetting& From
        );
        virtual ~FAppleAppStoreSetting() override = default;

        TSharedPtr<FAppleAppStoreSetting> WithBundleId(const TOptional<FString> BundleId);
        TSharedPtr<FAppleAppStoreSetting> WithTeamId(const TOptional<FString> TeamId);
        TSharedPtr<FAppleAppStoreSetting> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FAppleAppStoreSetting> WithPrivateKeyPem(const TOptional<FString> PrivateKeyPem);

        TOptional<FString> GetBundleId() const;
        TOptional<FString> GetTeamId() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetPrivateKeyPem() const;


        static TSharedPtr<FAppleAppStoreSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAppleAppStoreSetting, ESPMode::ThreadSafe> FAppleAppStoreSettingPtr;
}