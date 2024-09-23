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
    class FUpdateNotificationTypeRequest;

    class GS2CHAT_API FUpdateNotificationTypeRequest final : public TSharedFromThis<FUpdateNotificationTypeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateNotificationTypeRequest();
        FUpdateNotificationTypeRequest(
            const FUpdateNotificationTypeRequest& From
        );
        ~FUpdateNotificationTypeRequest() = default;

        TSharedPtr<FUpdateNotificationTypeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNotificationTypeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNotificationTypeRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FUpdateNotificationTypeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateNotificationTypeRequest> WithNotificationTypes(const TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypes);
        TSharedPtr<FUpdateNotificationTypeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> GetNotificationTypes() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateNotificationTypeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNotificationTypeRequest, ESPMode::ThreadSafe> FUpdateNotificationTypeRequestPtr;
}