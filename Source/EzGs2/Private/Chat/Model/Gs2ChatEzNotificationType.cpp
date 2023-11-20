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

#include "Chat/Model/Gs2ChatEzNotificationType.h"

namespace Gs2::UE5::Chat::Model
{

    TSharedPtr<FEzNotificationType> FEzNotificationType::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FEzNotificationType> FEzNotificationType::WithEnableTransferMobilePushNotification(
        const TOptional<bool> EnableTransferMobilePushNotification
    )
    {
        this->EnableTransferMobilePushNotificationValue = EnableTransferMobilePushNotification;
        return SharedThis(this);
    }
    TOptional<int32> FEzNotificationType::GetCategory() const
    {
        return CategoryValue;
    }

    FString FEzNotificationType::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }
    TOptional<bool> FEzNotificationType::GetEnableTransferMobilePushNotification() const
    {
        return EnableTransferMobilePushNotificationValue;
    }

    FString FEzNotificationType::GetEnableTransferMobilePushNotificationString() const
    {
        if (!EnableTransferMobilePushNotificationValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableTransferMobilePushNotificationValue.GetValue() ? "true" : "false");
    }

    Gs2::Chat::Model::FNotificationTypePtr FEzNotificationType::ToModel() const
    {
        return MakeShared<Gs2::Chat::Model::FNotificationType>()
            ->WithCategory(CategoryValue)
            ->WithEnableTransferMobilePushNotification(EnableTransferMobilePushNotificationValue);
    }

    TSharedPtr<FEzNotificationType> FEzNotificationType::FromModel(const Gs2::Chat::Model::FNotificationTypePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzNotificationType>()
            ->WithCategory(Model->GetCategory())
            ->WithEnableTransferMobilePushNotification(Model->GetEnableTransferMobilePushNotification());
    }
}