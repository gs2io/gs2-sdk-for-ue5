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

namespace Gs2::Stamina::Request
{
    class FDescribeStaminasByUserIdRequest;

    class GS2STAMINA_API FDescribeStaminasByUserIdRequest final : public TSharedFromThis<FDescribeStaminasByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeStaminasByUserIdRequest();
        FDescribeStaminasByUserIdRequest(
            const FDescribeStaminasByUserIdRequest& From
        );
        ~FDescribeStaminasByUserIdRequest() = default;

        TSharedPtr<FDescribeStaminasByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeStaminasByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeStaminasByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeStaminasByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeStaminasByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeStaminasByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeStaminasByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStaminasByUserIdRequest> FDescribeStaminasByUserIdRequestPtr;
}