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
    class FVerifyFollowRequest;

    class GS2FRIEND_API FVerifyFollowRequest final : public TSharedFromThis<FVerifyFollowRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyFollowRequest();
        FVerifyFollowRequest(
            const FVerifyFollowRequest& From
        );
        ~FVerifyFollowRequest() = default;

        TSharedPtr<FVerifyFollowRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyFollowRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyFollowRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyFollowRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FVerifyFollowRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyFollowRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyFollowRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyFollowRequest> FVerifyFollowRequestPtr;
}