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
    class FGetFollowByUserIdRequest;

    class GS2FRIEND_API FGetFollowByUserIdRequest final : public TSharedFromThis<FGetFollowByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<bool> WithProfileValue;
        
    public:
        
        FGetFollowByUserIdRequest();
        FGetFollowByUserIdRequest(
            const FGetFollowByUserIdRequest& From
        );
        ~FGetFollowByUserIdRequest() = default;

        TSharedPtr<FGetFollowByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFollowByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFollowByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetFollowByUserIdRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FGetFollowByUserIdRequest> WithWithProfile(const TOptional<bool> WithProfile);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;

        static TSharedPtr<FGetFollowByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFollowByUserIdRequest, ESPMode::ThreadSafe> FGetFollowByUserIdRequestPtr;
}