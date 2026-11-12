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
    class GS2ACCOUNT_API FAccountDeletionSetting final : public FGs2Object, public TSharedFromThis<FAccountDeletionSetting>
    {
        TOptional<int32> GracePeriodMinutesValue;
        TOptional<FString> LoginDuringGracePeriodValue;
        TOptional<FString> CleanUserDataScopeValue;

    public:
        FAccountDeletionSetting();
        FAccountDeletionSetting(
            const FAccountDeletionSetting& From
        );
        virtual ~FAccountDeletionSetting() override = default;

        TSharedPtr<FAccountDeletionSetting> WithGracePeriodMinutes(const TOptional<int32> GracePeriodMinutes);
        TSharedPtr<FAccountDeletionSetting> WithLoginDuringGracePeriod(const TOptional<FString> LoginDuringGracePeriod);
        TSharedPtr<FAccountDeletionSetting> WithCleanUserDataScope(const TOptional<FString> CleanUserDataScope);

        TOptional<int32> GetGracePeriodMinutes() const;
        FString GetGracePeriodMinutesString() const;
        TOptional<FString> GetLoginDuringGracePeriod() const;
        TOptional<FString> GetCleanUserDataScope() const;


        static TSharedPtr<FAccountDeletionSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccountDeletionSetting, ESPMode::ThreadSafe> FAccountDeletionSettingPtr;
}