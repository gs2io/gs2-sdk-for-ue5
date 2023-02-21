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
    class FDescribeReceiptsRequest;

    class GS2MONEY_API FDescribeReceiptsRequest final : public TSharedFromThis<FDescribeReceiptsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> SlotValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeReceiptsRequest();
        FDescribeReceiptsRequest(
            const FDescribeReceiptsRequest& From
        );
        ~FDescribeReceiptsRequest() = default;

        TSharedPtr<FDescribeReceiptsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeReceiptsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeReceiptsRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeReceiptsRequest> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FDescribeReceiptsRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FDescribeReceiptsRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FDescribeReceiptsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeReceiptsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeReceiptsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeReceiptsRequest, ESPMode::ThreadSafe> FDescribeReceiptsRequestPtr;
}