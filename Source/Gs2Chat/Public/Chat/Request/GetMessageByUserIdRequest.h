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
    class FGetMessageByUserIdRequest;

    class GS2CHAT_API FGetMessageByUserIdRequest final : public TSharedFromThis<FGetMessageByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> MessageNameValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetMessageByUserIdRequest();
        FGetMessageByUserIdRequest(
            const FGetMessageByUserIdRequest& From
        );
        ~FGetMessageByUserIdRequest() = default;

        TSharedPtr<FGetMessageByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMessageByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMessageByUserIdRequest> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FGetMessageByUserIdRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FGetMessageByUserIdRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FGetMessageByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetMessageByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRoomName() const;
        TOptional<FString> GetMessageName() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetMessageByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMessageByUserIdRequest> FGetMessageByUserIdRequestPtr;
}