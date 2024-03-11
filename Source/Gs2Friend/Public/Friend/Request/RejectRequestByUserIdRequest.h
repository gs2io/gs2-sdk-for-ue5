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
    class FRejectRequestByUserIdRequest;

    class GS2FRIEND_API FRejectRequestByUserIdRequest final : public TSharedFromThis<FRejectRequestByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> FromUserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRejectRequestByUserIdRequest();
        FRejectRequestByUserIdRequest(
            const FRejectRequestByUserIdRequest& From
        );
        ~FRejectRequestByUserIdRequest() = default;

        TSharedPtr<FRejectRequestByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRejectRequestByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRejectRequestByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRejectRequestByUserIdRequest> WithFromUserId(const TOptional<FString> FromUserId);
        TSharedPtr<FRejectRequestByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRejectRequestByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetFromUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRejectRequestByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRejectRequestByUserIdRequest, ESPMode::ThreadSafe> FRejectRequestByUserIdRequestPtr;
}