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
#include "../Model/Receipt.h"

namespace Gs2::Money2::Request
{
    class FTakeoverSubscriptionStatusByUserIdRequest;

    class GS2MONEY2_API FTakeoverSubscriptionStatusByUserIdRequest final : public TSharedFromThis<FTakeoverSubscriptionStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FReceipt> ReceiptValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FTakeoverSubscriptionStatusByUserIdRequest();
        FTakeoverSubscriptionStatusByUserIdRequest(
            const FTakeoverSubscriptionStatusByUserIdRequest& From
        );
        ~FTakeoverSubscriptionStatusByUserIdRequest() = default;

        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithReceipt(const TSharedPtr<Model::FReceipt> Receipt);
        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FReceipt> GetReceipt() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FTakeoverSubscriptionStatusByUserIdRequest> FTakeoverSubscriptionStatusByUserIdRequestPtr;
}