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
#include "../Model/NotificationType.h"

namespace Gs2::Chat::Request
{
    class FUpdateNotificationTypeByUserIdRequest;

    class GS2CHAT_API FUpdateNotificationTypeByUserIdRequest final : public TSharedFromThis<FUpdateNotificationTypeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateNotificationTypeByUserIdRequest();
        FUpdateNotificationTypeByUserIdRequest(
            const FUpdateNotificationTypeByUserIdRequest& From
        );
        ~FUpdateNotificationTypeByUserIdRequest() = default;

        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithNotificationTypes(const TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypes);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateNotificationTypeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> GetNotificationTypes() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateNotificationTypeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNotificationTypeByUserIdRequest, ESPMode::ThreadSafe> FUpdateNotificationTypeByUserIdRequestPtr;
}