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

namespace Gs2::Realtime::Model
{
    class GS2REALTIME_API FNotificationSetting final : public FGs2Object, public TSharedFromThis<FNotificationSetting>
    {
        TOptional<FString> GatewayNamespaceIdValue;
        TOptional<bool> EnableTransferMobileNotificationValue;
        TOptional<FString> SoundValue;

    public:
        FNotificationSetting();
        FNotificationSetting(
            const FNotificationSetting& From
        );
        virtual ~FNotificationSetting() override = default;

        TSharedPtr<FNotificationSetting> WithGatewayNamespaceId(const TOptional<FString> GatewayNamespaceId);
        TSharedPtr<FNotificationSetting> WithEnableTransferMobileNotification(const TOptional<bool> EnableTransferMobileNotification);
        TSharedPtr<FNotificationSetting> WithSound(const TOptional<FString> Sound);

        TOptional<FString> GetGatewayNamespaceId() const;
        TOptional<bool> GetEnableTransferMobileNotification() const;
        FString GetEnableTransferMobileNotificationString() const;
        TOptional<FString> GetSound() const;


        static TSharedPtr<FNotificationSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNotificationSetting, ESPMode::ThreadSafe> FNotificationSettingPtr;
}