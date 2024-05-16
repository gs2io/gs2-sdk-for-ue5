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

#include "Chat/Model/NotificationType.h"

namespace Gs2::Chat::Model
{
    FNotificationType::FNotificationType():
        CategoryValue(TOptional<int32>()),
        EnableTransferMobilePushNotificationValue(TOptional<bool>())
    {
    }

    FNotificationType::FNotificationType(
        const FNotificationType& From
    ):
        CategoryValue(From.CategoryValue),
        EnableTransferMobilePushNotificationValue(From.EnableTransferMobilePushNotificationValue)
    {
    }

    TSharedPtr<FNotificationType> FNotificationType::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FNotificationType> FNotificationType::WithEnableTransferMobilePushNotification(
        const TOptional<bool> EnableTransferMobilePushNotification
    )
    {
        this->EnableTransferMobilePushNotificationValue = EnableTransferMobilePushNotification;
        return SharedThis(this);
    }
    TOptional<int32> FNotificationType::GetCategory() const
    {
        return CategoryValue;
    }

    FString FNotificationType::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }
    TOptional<bool> FNotificationType::GetEnableTransferMobilePushNotification() const
    {
        return EnableTransferMobilePushNotificationValue;
    }

    FString FNotificationType::GetEnableTransferMobilePushNotificationString() const
    {
        if (!EnableTransferMobilePushNotificationValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableTransferMobilePushNotificationValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FNotificationType> FNotificationType::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNotificationType>()
            ->WithCategory(Data->HasField(ANSI_TO_TCHAR("category")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("category"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEnableTransferMobilePushNotification(Data->HasField(ANSI_TO_TCHAR("enableTransferMobilePushNotification")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableTransferMobilePushNotification"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FNotificationType::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CategoryValue.IsSet())
        {
            JsonRootObject->SetNumberField("category", CategoryValue.GetValue());
        }
        if (EnableTransferMobilePushNotificationValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableTransferMobilePushNotification", EnableTransferMobilePushNotificationValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FNotificationType::TypeName = "NotificationType";
}