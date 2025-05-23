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
    class FGetWalletRequest;

    class GS2MONEY2_API FGetWalletRequest final : public TSharedFromThis<FGetWalletRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> SlotValue;
        
    public:
        
        FGetWalletRequest();
        FGetWalletRequest(
            const FGetWalletRequest& From
        );
        ~FGetWalletRequest() = default;

        TSharedPtr<FGetWalletRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetWalletRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetWalletRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetWalletRequest> WithSlot(const TOptional<int32> Slot);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;

        static TSharedPtr<FGetWalletRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetWalletRequest> FGetWalletRequestPtr;
}