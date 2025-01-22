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
#include "Dom/JsonObject.h"
#include "../Model/NotificationType.h"

namespace Gs2::Chat::Request
{
    class FSubscribeByUserIdRequest;

    class GS2CHAT_API FSubscribeByUserIdRequest final : public TSharedFromThis<FSubscribeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSubscribeByUserIdRequest();
        FSubscribeByUserIdRequest(
            const FSubscribeByUserIdRequest& From
        );
        ~FSubscribeByUserIdRequest() = default;

        TSharedPtr<FSubscribeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSubscribeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSubscribeByUserIdRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FSubscribeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribeByUserIdRequest> WithNotificationTypes(const TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypes);
        TSharedPtr<FSubscribeByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSubscribeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> GetNotificationTypes() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSubscribeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequestPtr;
}