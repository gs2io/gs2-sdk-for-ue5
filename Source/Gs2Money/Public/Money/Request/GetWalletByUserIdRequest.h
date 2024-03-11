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

namespace Gs2::Money::Request
{
    class FGetWalletByUserIdRequest;

    class GS2MONEY_API FGetWalletByUserIdRequest final : public TSharedFromThis<FGetWalletByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> SlotValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetWalletByUserIdRequest();
        FGetWalletByUserIdRequest(
            const FGetWalletByUserIdRequest& From
        );
        ~FGetWalletByUserIdRequest() = default;

        TSharedPtr<FGetWalletByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetWalletByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetWalletByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetWalletByUserIdRequest> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FGetWalletByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetWalletByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetWalletByUserIdRequest, ESPMode::ThreadSafe> FGetWalletByUserIdRequestPtr;
}