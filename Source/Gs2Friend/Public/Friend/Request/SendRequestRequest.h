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
    class FSendRequestRequest;

    class GS2FRIEND_API FSendRequestRequest final : public TSharedFromThis<FSendRequestRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendRequestRequest();
        FSendRequestRequest(
            const FSendRequestRequest& From
        );
        ~FSendRequestRequest() = default;

        TSharedPtr<FSendRequestRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendRequestRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendRequestRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSendRequestRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FSendRequestRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendRequestRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendRequestRequest> FSendRequestRequestPtr;
}