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

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FNotificationType final : public TSharedFromThis<FNotificationType>
    {
        TOptional<int32> CategoryValue;
        TOptional<bool> EnableTransferMobilePushNotificationValue;

    public:
        FNotificationType();
        FNotificationType(
            const FNotificationType& From
        );
        ~FNotificationType() = default;

        TSharedPtr<FNotificationType> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FNotificationType> WithEnableTransferMobilePushNotification(const TOptional<bool> EnableTransferMobilePushNotification);

        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<bool> GetEnableTransferMobilePushNotification() const;
        FString GetEnableTransferMobilePushNotificationString() const;


        static TSharedPtr<FNotificationType> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNotificationType, ESPMode::ThreadSafe> FNotificationTypePtr;
}