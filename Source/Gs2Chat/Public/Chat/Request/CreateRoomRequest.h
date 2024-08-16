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
    class FCreateRoomRequest;

    class GS2CHAT_API FCreateRoomRequest final : public TSharedFromThis<FCreateRoomRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PasswordValue;
        TSharedPtr<TArray<FString>> WhiteListUserIdsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateRoomRequest();
        FCreateRoomRequest(
            const FCreateRoomRequest& From
        );
        ~FCreateRoomRequest() = default;

        TSharedPtr<FCreateRoomRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRoomRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRoomRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FCreateRoomRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRoomRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRoomRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FCreateRoomRequest> WithWhiteListUserIds(
            const TSharedPtr<TArray<FString>> WhiteListUserIds);
        TSharedPtr<FCreateRoomRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPassword() const;
        TSharedPtr<TArray<FString>> GetWhiteListUserIds() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateRoomRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRoomRequest> FCreateRoomRequestPtr;
}