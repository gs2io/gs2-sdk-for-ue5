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
    class FTakeoverSubscriptionStatusRequest;

    class GS2MONEY2_API FTakeoverSubscriptionStatusRequest final : public TSharedFromThis<FTakeoverSubscriptionStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ReceiptValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FTakeoverSubscriptionStatusRequest();
        FTakeoverSubscriptionStatusRequest(
            const FTakeoverSubscriptionStatusRequest& From
        );
        ~FTakeoverSubscriptionStatusRequest() = default;

        TSharedPtr<FTakeoverSubscriptionStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FTakeoverSubscriptionStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FTakeoverSubscriptionStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FTakeoverSubscriptionStatusRequest> WithReceipt(const TOptional<FString> Receipt);
        TSharedPtr<FTakeoverSubscriptionStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetReceipt() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FTakeoverSubscriptionStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FTakeoverSubscriptionStatusRequest> FTakeoverSubscriptionStatusRequestPtr;
}