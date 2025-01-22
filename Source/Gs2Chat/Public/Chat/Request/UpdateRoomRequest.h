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
    class FUpdateRoomRequest;

    class GS2CHAT_API FUpdateRoomRequest final : public TSharedFromThis<FUpdateRoomRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateRoomRequest();
        FUpdateRoomRequest(
            const FUpdateRoomRequest& From
        );
        ~FUpdateRoomRequest() = default;

        TSharedPtr<FUpdateRoomRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRoomRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRoomRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FUpdateRoomRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRoomRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FUpdateRoomRequest> WithWhiteListUserIds(
            const TSharedPtr<TArray<FString>> WhiteListUserIds);
        TSharedPtr<FUpdateRoomRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateRoomRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateRoomRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRoomRequest> FUpdateRoomRequestPtr;
}