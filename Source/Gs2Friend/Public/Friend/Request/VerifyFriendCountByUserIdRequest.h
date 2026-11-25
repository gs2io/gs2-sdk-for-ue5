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
    class FVerifyFriendCountByUserIdRequest;

    class GS2FRIEND_API FVerifyFriendCountByUserIdRequest final : public TSharedFromThis<FVerifyFriendCountByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyFriendCountByUserIdRequest();
        FVerifyFriendCountByUserIdRequest(
            const FVerifyFriendCountByUserIdRequest& From
        );
        ~FVerifyFriendCountByUserIdRequest() = default;

        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyFriendCountByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyFriendCountByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyFriendCountByUserIdRequest> FVerifyFriendCountByUserIdRequestPtr;
}