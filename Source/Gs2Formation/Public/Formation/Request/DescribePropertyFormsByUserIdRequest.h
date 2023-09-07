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

namespace Gs2::Formation::Request
{
    class FDescribePropertyFormsByUserIdRequest;

    class GS2FORMATION_API FDescribePropertyFormsByUserIdRequest final : public TSharedFromThis<FDescribePropertyFormsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribePropertyFormsByUserIdRequest();
        FDescribePropertyFormsByUserIdRequest(
            const FDescribePropertyFormsByUserIdRequest& From
        );
        ~FDescribePropertyFormsByUserIdRequest() = default;

        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribePropertyFormsByUserIdRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribePropertyFormsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribePropertyFormsByUserIdRequest, ESPMode::ThreadSafe> FDescribePropertyFormsByUserIdRequestPtr;
}