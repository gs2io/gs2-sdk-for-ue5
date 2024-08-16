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

namespace Gs2::Guild::Request
{
    class FVerifyCurrentMaximumMemberCountByGuildNameRequest;

    class GS2GUILD_API FVerifyCurrentMaximumMemberCountByGuildNameRequest final : public TSharedFromThis<FVerifyCurrentMaximumMemberCountByGuildNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> ValueValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCurrentMaximumMemberCountByGuildNameRequest();
        FVerifyCurrentMaximumMemberCountByGuildNameRequest(
            const FVerifyCurrentMaximumMemberCountByGuildNameRequest& From
        );
        ~FVerifyCurrentMaximumMemberCountByGuildNameRequest() = default;

        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetGuildName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCurrentMaximumMemberCountByGuildNameRequest> FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr;
}