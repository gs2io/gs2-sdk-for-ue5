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

namespace Gs2::Money2::Request
{
    class FAllocateSubscriptionStatusByUserIdRequest;

    class GS2MONEY2_API FAllocateSubscriptionStatusByUserIdRequest final : public TSharedFromThis<FAllocateSubscriptionStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ReceiptValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAllocateSubscriptionStatusByUserIdRequest();
        FAllocateSubscriptionStatusByUserIdRequest(
            const FAllocateSubscriptionStatusByUserIdRequest& From
        );
        ~FAllocateSubscriptionStatusByUserIdRequest() = default;

        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithReceipt(const TOptional<FString> Receipt);
        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetReceipt() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAllocateSubscriptionStatusByUserIdRequest> FAllocateSubscriptionStatusByUserIdRequestPtr;
}