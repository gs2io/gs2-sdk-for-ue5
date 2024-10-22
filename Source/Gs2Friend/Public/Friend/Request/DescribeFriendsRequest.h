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
    class FDescribeFriendsRequest;

    class GS2FRIEND_API FDescribeFriendsRequest final : public TSharedFromThis<FDescribeFriendsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<bool> WithProfileValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeFriendsRequest();
        FDescribeFriendsRequest(
            const FDescribeFriendsRequest& From
        );
        ~FDescribeFriendsRequest() = default;

        TSharedPtr<FDescribeFriendsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeFriendsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeFriendsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeFriendsRequest> WithWithProfile(const TOptional<bool> WithProfile);
        TSharedPtr<FDescribeFriendsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeFriendsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeFriendsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeFriendsRequest> FDescribeFriendsRequestPtr;
}