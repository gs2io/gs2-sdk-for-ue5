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

namespace Gs2::Money::Request
{
    class FWithdrawRequest;

    class GS2MONEY_API FWithdrawRequest final : public TSharedFromThis<FWithdrawRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> SlotValue;
        TOptional<int32> CountValue;
        TOptional<bool> PaidOnlyValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FWithdrawRequest();
        FWithdrawRequest(
            const FWithdrawRequest& From
        );
        ~FWithdrawRequest() = default;

        TSharedPtr<FWithdrawRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FWithdrawRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FWithdrawRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FWithdrawRequest> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FWithdrawRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FWithdrawRequest> WithPaidOnly(const TOptional<bool> PaidOnly);
        TSharedPtr<FWithdrawRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<bool> GetPaidOnly() const;
        FString GetPaidOnlyString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FWithdrawRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWithdrawRequest> FWithdrawRequestPtr;
}