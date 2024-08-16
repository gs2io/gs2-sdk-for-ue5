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

namespace Gs2::Showcase::Request
{
    class FDescribeShowcasesByUserIdRequest;

    class GS2SHOWCASE_API FDescribeShowcasesByUserIdRequest final : public TSharedFromThis<FDescribeShowcasesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeShowcasesByUserIdRequest();
        FDescribeShowcasesByUserIdRequest(
            const FDescribeShowcasesByUserIdRequest& From
        );
        ~FDescribeShowcasesByUserIdRequest() = default;

        TSharedPtr<FDescribeShowcasesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeShowcasesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeShowcasesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeShowcasesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeShowcasesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeShowcasesByUserIdRequest> FDescribeShowcasesByUserIdRequestPtr;
}