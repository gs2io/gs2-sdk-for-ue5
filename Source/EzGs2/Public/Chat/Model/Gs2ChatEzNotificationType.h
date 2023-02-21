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
#include "Chat/Model/NotificationType.h"

namespace Gs2::UE5::Chat::Model
{
	class EZGS2_API FEzNotificationType final : public TSharedFromThis<FEzNotificationType>
	{
        TOptional<int32> CategoryValue;
        TOptional<bool> EnableTransferMobilePushNotificationValue;

	public:
        TSharedPtr<FEzNotificationType> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FEzNotificationType> WithEnableTransferMobilePushNotification(const TOptional<bool> EnableTransferMobilePushNotification);

        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;

        TOptional<bool> GetEnableTransferMobilePushNotification() const;
        FString GetEnableTransferMobilePushNotificationString() const;

        Gs2::Chat::Model::FNotificationTypePtr ToModel() const;
        static TSharedPtr<FEzNotificationType> FromModel(Gs2::Chat::Model::FNotificationTypePtr Model);
    };
    typedef TSharedPtr<FEzNotificationType> FEzNotificationTypePtr;
}