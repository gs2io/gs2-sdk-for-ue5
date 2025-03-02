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
    class FAllocateSubscriptionStatusRequest;

    class GS2MONEY2_API FAllocateSubscriptionStatusRequest final : public TSharedFromThis<FAllocateSubscriptionStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<Model::FReceipt> ReceiptValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAllocateSubscriptionStatusRequest();
        FAllocateSubscriptionStatusRequest(
            const FAllocateSubscriptionStatusRequest& From
        );
        ~FAllocateSubscriptionStatusRequest() = default;

        TSharedPtr<FAllocateSubscriptionStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAllocateSubscriptionStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAllocateSubscriptionStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAllocateSubscriptionStatusRequest> WithReceipt(const TSharedPtr<Model::FReceipt> Receipt);
        TSharedPtr<FAllocateSubscriptionStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<Model::FReceipt> GetReceipt() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAllocateSubscriptionStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAllocateSubscriptionStatusRequest> FAllocateSubscriptionStatusRequestPtr;
}