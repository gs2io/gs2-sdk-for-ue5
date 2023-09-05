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

namespace Gs2::Showcase::Request
{
    class FDecrementPurchaseCountByUserIdRequest;

    class GS2SHOWCASE_API FDecrementPurchaseCountByUserIdRequest final : public TSharedFromThis<FDecrementPurchaseCountByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecrementPurchaseCountByUserIdRequest();
        FDecrementPurchaseCountByUserIdRequest(
            const FDecrementPurchaseCountByUserIdRequest& From
        );
        ~FDecrementPurchaseCountByUserIdRequest() = default;

        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FDecrementPurchaseCountByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecrementPurchaseCountByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecrementPurchaseCountByUserIdRequest, ESPMode::ThreadSafe> FDecrementPurchaseCountByUserIdRequestPtr;
}