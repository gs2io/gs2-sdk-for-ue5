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

#include "Chat/Model/Gs2ChatEzNotificationType.h"
#include "Gs2ChatNotificationType.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatNotificationType
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Category = 0;
    UPROPERTY(BlueprintReadWrite)
    bool EnableTransferMobilePushNotification = false;
};

inline FGs2ChatNotificationType EzNotificationTypeToFGs2ChatNotificationType(
    const Gs2::UE5::Chat::Model::FEzNotificationTypePtr Model
)
{
    FGs2ChatNotificationType Value;
    Value.Category = Model->GetCategory() ? *Model->GetCategory() : 0;
    Value.EnableTransferMobilePushNotification = Model->GetEnableTransferMobilePushNotification() ? *Model->GetEnableTransferMobilePushNotification() : false;
    return Value;
}

inline Gs2::UE5::Chat::Model::FEzNotificationTypePtr FGs2ChatNotificationTypeToEzNotificationType(
    const FGs2ChatNotificationType Model
)
{
    return MakeShared<Gs2::UE5::Chat::Model::FEzNotificationType>()
        ->WithCategory(Model.Category)
        ->WithEnableTransferMobilePushNotification(Model.EnableTransferMobilePushNotification);
}