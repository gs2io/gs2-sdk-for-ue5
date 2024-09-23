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
    class FCreateRoomFromBackendRequest;

    class GS2CHAT_API FCreateRoomFromBackendRequest final : public TSharedFromThis<FCreateRoomFromBackendRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateRoomFromBackendRequest();
        FCreateRoomFromBackendRequest(
            const FCreateRoomFromBackendRequest& From
        );
        ~FCreateRoomFromBackendRequest() = default;

        TSharedPtr<FCreateRoomFromBackendRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRoomFromBackendRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRoomFromBackendRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRoomFromBackendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateRoomFromBackendRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRoomFromBackendRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FCreateRoomFromBackendRequest> WithWhiteListUserIds(
            const TSharedPtr<TArray<FString>> WhiteListUserIds);
        TSharedPtr<FCreateRoomFromBackendRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateRoomFromBackendRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateRoomFromBackendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRoomFromBackendRequest, ESPMode::ThreadSafe> FCreateRoomFromBackendRequestPtr;
}