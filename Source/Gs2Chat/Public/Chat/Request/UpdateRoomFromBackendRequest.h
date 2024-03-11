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

namespace Gs2::Chat::Request
{
    class FUpdateRoomFromBackendRequest;

    class GS2CHAT_API FUpdateRoomFromBackendRequest final : public TSharedFromThis<FUpdateRoomFromBackendRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateRoomFromBackendRequest();
        FUpdateRoomFromBackendRequest(
            const FUpdateRoomFromBackendRequest& From
        );
        ~FUpdateRoomFromBackendRequest() = default;

        TSharedPtr<FUpdateRoomFromBackendRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithWhiteListUserIds(
            const TSharedPtr<TArray<FString>> WhiteListUserIds);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateRoomFromBackendRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateRoomFromBackendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRoomFromBackendRequest, ESPMode::ThreadSafe> FUpdateRoomFromBackendRequestPtr;
}