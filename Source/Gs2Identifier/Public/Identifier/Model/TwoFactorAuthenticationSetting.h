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

namespace Gs2::Identifier::Model
{
    class GS2IDENTIFIER_API FTwoFactorAuthenticationSetting final : public FGs2Object, public TSharedFromThis<FTwoFactorAuthenticationSetting>
    {
        TOptional<FString> StatusValue;

    public:
        FTwoFactorAuthenticationSetting();
        FTwoFactorAuthenticationSetting(
            const FTwoFactorAuthenticationSetting& From
        );
        virtual ~FTwoFactorAuthenticationSetting() override = default;

        TSharedPtr<FTwoFactorAuthenticationSetting> WithStatus(const TOptional<FString> Status);

        TOptional<FString> GetStatus() const;


        static TSharedPtr<FTwoFactorAuthenticationSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTwoFactorAuthenticationSetting, ESPMode::ThreadSafe> FTwoFactorAuthenticationSettingPtr;
}