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

namespace Gs2::Guild::Request
{
    class FVerifyCurrentMaximumMemberCountRequest;

    class GS2GUILD_API FVerifyCurrentMaximumMemberCountRequest final : public TSharedFromThis<FVerifyCurrentMaximumMemberCountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCurrentMaximumMemberCountRequest();
        FVerifyCurrentMaximumMemberCountRequest(
            const FVerifyCurrentMaximumMemberCountRequest& From
        );
        ~FVerifyCurrentMaximumMemberCountRequest() = default;

        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCurrentMaximumMemberCountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCurrentMaximumMemberCountRequest, ESPMode::ThreadSafe> FVerifyCurrentMaximumMemberCountRequestPtr;
}