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

namespace Gs2::Datastore::Request
{
    class FDescribeDataObjectHistoriesByUserIdRequest;

    class GS2DATASTORE_API FDescribeDataObjectHistoriesByUserIdRequest final : public TSharedFromThis<FDescribeDataObjectHistoriesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeDataObjectHistoriesByUserIdRequest();
        FDescribeDataObjectHistoriesByUserIdRequest(
            const FDescribeDataObjectHistoriesByUserIdRequest& From
        );
        ~FDescribeDataObjectHistoriesByUserIdRequest() = default;

        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeDataObjectHistoriesByUserIdRequest> FDescribeDataObjectHistoriesByUserIdRequestPtr;
}