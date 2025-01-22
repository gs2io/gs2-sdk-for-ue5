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

namespace Gs2::Chat::Request
{
    class FDeleteRoomRequest;

    class GS2CHAT_API FDeleteRoomRequest final : public TSharedFromThis<FDeleteRoomRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteRoomRequest();
        FDeleteRoomRequest(
            const FDeleteRoomRequest& From
        );
        ~FDeleteRoomRequest() = default;

        TSharedPtr<FDeleteRoomRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteRoomRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteRoomRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FDeleteRoomRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteRoomRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteRoomRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteRoomRequest> FDeleteRoomRequestPtr;
}