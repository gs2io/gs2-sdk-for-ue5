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
    class FGetFollowRequest;

    class GS2FRIEND_API FGetFollowRequest final : public TSharedFromThis<FGetFollowRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<bool> WithProfileValue;
        
    public:
        
        FGetFollowRequest();
        FGetFollowRequest(
            const FGetFollowRequest& From
        );
        ~FGetFollowRequest() = default;

        TSharedPtr<FGetFollowRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFollowRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFollowRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetFollowRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FGetFollowRequest> WithWithProfile(const TOptional<bool> WithProfile);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;

        static TSharedPtr<FGetFollowRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFollowRequest> FGetFollowRequestPtr;
}