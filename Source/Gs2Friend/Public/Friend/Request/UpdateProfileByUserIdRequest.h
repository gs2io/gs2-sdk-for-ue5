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

namespace Gs2::Friend::Request
{
    class FUpdateProfileByUserIdRequest;

    class GS2FRIEND_API FUpdateProfileByUserIdRequest final : public TSharedFromThis<FUpdateProfileByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FollowerProfileValue;
        TOptional<FString> FriendProfileValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateProfileByUserIdRequest();
        FUpdateProfileByUserIdRequest(
            const FUpdateProfileByUserIdRequest& From
        );
        ~FUpdateProfileByUserIdRequest() = default;

        TSharedPtr<FUpdateProfileByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithFollowerProfile(const TOptional<FString> FollowerProfile);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithFriendProfile(const TOptional<FString> FriendProfile);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateProfileByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPublicProfile() const;
        TOptional<FString> GetFollowerProfile() const;
        TOptional<FString> GetFriendProfile() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateProfileByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateProfileByUserIdRequest, ESPMode::ThreadSafe> FUpdateProfileByUserIdRequestPtr;
}