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

namespace Gs2::Dictionary::Request
{
    class FDescribeEntriesByUserIdRequest;

    class GS2DICTIONARY_API FDescribeEntriesByUserIdRequest final : public TSharedFromThis<FDescribeEntriesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeEntriesByUserIdRequest();
        FDescribeEntriesByUserIdRequest(
            const FDescribeEntriesByUserIdRequest& From
        );
        ~FDescribeEntriesByUserIdRequest() = default;

        TSharedPtr<FDescribeEntriesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeEntriesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeEntriesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeEntriesByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeEntriesByUserIdRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeEntriesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeEntriesByUserIdRequest, ESPMode::ThreadSafe> FDescribeEntriesByUserIdRequestPtr;
}