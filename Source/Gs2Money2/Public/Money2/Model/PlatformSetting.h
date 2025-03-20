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
#include "AppleAppStoreSetting.h"
#include "GooglePlaySetting.h"
#include "FakeSetting.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FPlatformSetting final : public FGs2Object, public TSharedFromThis<FPlatformSetting>
    {
        TSharedPtr<FAppleAppStoreSetting> AppleAppStoreValue;
        TSharedPtr<FGooglePlaySetting> GooglePlayValue;
        TSharedPtr<FFakeSetting> FakeValue;

    public:
        FPlatformSetting();
        FPlatformSetting(
            const FPlatformSetting& From
        );
        virtual ~FPlatformSetting() override = default;

        TSharedPtr<FPlatformSetting> WithAppleAppStore(const TSharedPtr<FAppleAppStoreSetting> AppleAppStore);
        TSharedPtr<FPlatformSetting> WithGooglePlay(const TSharedPtr<FGooglePlaySetting> GooglePlay);
        TSharedPtr<FPlatformSetting> WithFake(const TSharedPtr<FFakeSetting> Fake);

        TSharedPtr<FAppleAppStoreSetting> GetAppleAppStore() const;
        TSharedPtr<FGooglePlaySetting> GetGooglePlay() const;
        TSharedPtr<FFakeSetting> GetFake() const;


        static TSharedPtr<FPlatformSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPlatformSetting, ESPMode::ThreadSafe> FPlatformSettingPtr;
}