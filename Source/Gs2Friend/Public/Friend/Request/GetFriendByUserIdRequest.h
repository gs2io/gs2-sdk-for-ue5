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

namespace Gs2::Friend::Request
{
    class FGetFriendByUserIdRequest;

    class GS2FRIEND_API FGetFriendByUserIdRequest final : public TSharedFromThis<FGetFriendByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<bool> WithProfileValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetFriendByUserIdRequest();
        FGetFriendByUserIdRequest(
            const FGetFriendByUserIdRequest& From
        );
        ~FGetFriendByUserIdRequest() = default;

        TSharedPtr<FGetFriendByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFriendByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFriendByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetFriendByUserIdRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FGetFriendByUserIdRequest> WithWithProfile(const TOptional<bool> WithProfile);
        TSharedPtr<FGetFriendByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetFriendByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFriendByUserIdRequest> FGetFriendByUserIdRequestPtr;
}