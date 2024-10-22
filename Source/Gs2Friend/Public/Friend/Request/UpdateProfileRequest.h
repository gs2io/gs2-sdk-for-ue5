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
    class FUpdateProfileRequest;

    class GS2FRIEND_API FUpdateProfileRequest final : public TSharedFromThis<FUpdateProfileRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FollowerProfileValue;
        TOptional<FString> FriendProfileValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateProfileRequest();
        FUpdateProfileRequest(
            const FUpdateProfileRequest& From
        );
        ~FUpdateProfileRequest() = default;

        TSharedPtr<FUpdateProfileRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateProfileRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateProfileRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUpdateProfileRequest> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FUpdateProfileRequest> WithFollowerProfile(const TOptional<FString> FollowerProfile);
        TSharedPtr<FUpdateProfileRequest> WithFriendProfile(const TOptional<FString> FriendProfile);
        TSharedPtr<FUpdateProfileRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPublicProfile() const;
        TOptional<FString> GetFollowerProfile() const;
        TOptional<FString> GetFriendProfile() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateProfileRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequestPtr;
}