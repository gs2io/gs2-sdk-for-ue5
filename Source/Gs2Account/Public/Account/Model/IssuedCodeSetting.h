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
    class GS2ACCOUNT_API FIssuedCodeSetting final : public FGs2Object, public TSharedFromThis<FIssuedCodeSetting>
    {
        TOptional<int32> ExpiresDaysValue;
        TOptional<int32> MaxFailedAttemptsValue;
        TOptional<bool> DeleteOnUseValue;

    public:
        FIssuedCodeSetting();
        FIssuedCodeSetting(
            const FIssuedCodeSetting& From
        );
        virtual ~FIssuedCodeSetting() override = default;

        TSharedPtr<FIssuedCodeSetting> WithExpiresDays(const TOptional<int32> ExpiresDays);
        TSharedPtr<FIssuedCodeSetting> WithMaxFailedAttempts(const TOptional<int32> MaxFailedAttempts);
        TSharedPtr<FIssuedCodeSetting> WithDeleteOnUse(const TOptional<bool> DeleteOnUse);

        TOptional<int32> GetExpiresDays() const;
        FString GetExpiresDaysString() const;
        TOptional<int32> GetMaxFailedAttempts() const;
        FString GetMaxFailedAttemptsString() const;
        TOptional<bool> GetDeleteOnUse() const;
        FString GetDeleteOnUseString() const;


        static TSharedPtr<FIssuedCodeSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FIssuedCodeSetting, ESPMode::ThreadSafe> FIssuedCodeSettingPtr;
}