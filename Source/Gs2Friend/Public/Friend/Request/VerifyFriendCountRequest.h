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
    class FVerifyFriendCountRequest;

    class GS2FRIEND_API FVerifyFriendCountRequest final : public TSharedFromThis<FVerifyFriendCountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyFriendCountRequest();
        FVerifyFriendCountRequest(
            const FVerifyFriendCountRequest& From
        );
        ~FVerifyFriendCountRequest() = default;

        TSharedPtr<FVerifyFriendCountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyFriendCountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyFriendCountRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyFriendCountRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyFriendCountRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyFriendCountRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyFriendCountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyFriendCountRequest> FVerifyFriendCountRequestPtr;
}