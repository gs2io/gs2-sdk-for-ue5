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
    class FUnfollowRequest;

    class GS2FRIEND_API FUnfollowRequest final : public TSharedFromThis<FUnfollowRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnfollowRequest();
        FUnfollowRequest(
            const FUnfollowRequest& From
        );
        ~FUnfollowRequest() = default;

        TSharedPtr<FUnfollowRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnfollowRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnfollowRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUnfollowRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FUnfollowRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnfollowRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnfollowRequest> FUnfollowRequestPtr;
}