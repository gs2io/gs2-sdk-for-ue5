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
    class FDeleteRoomFromBackendRequest;

    class GS2CHAT_API FDeleteRoomFromBackendRequest final : public TSharedFromThis<FDeleteRoomFromBackendRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteRoomFromBackendRequest();
        FDeleteRoomFromBackendRequest(
            const FDeleteRoomFromBackendRequest& From
        );
        ~FDeleteRoomFromBackendRequest() = default;

        TSharedPtr<FDeleteRoomFromBackendRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteRoomFromBackendRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteRoomFromBackendRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FDeleteRoomFromBackendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteRoomFromBackendRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteRoomFromBackendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteRoomFromBackendRequest, ESPMode::ThreadSafe> FDeleteRoomFromBackendRequestPtr;
}