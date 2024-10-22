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
    class FDescribeMaxStaminaTableMastersRequest;

    class GS2STAMINA_API FDescribeMaxStaminaTableMastersRequest final : public TSharedFromThis<FDescribeMaxStaminaTableMastersRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeMaxStaminaTableMastersRequest();
        FDescribeMaxStaminaTableMastersRequest(
            const FDescribeMaxStaminaTableMastersRequest& From
        );
        ~FDescribeMaxStaminaTableMastersRequest() = default;

        TSharedPtr<FDescribeMaxStaminaTableMastersRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeMaxStaminaTableMastersRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeMaxStaminaTableMastersRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeMaxStaminaTableMastersRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeMaxStaminaTableMastersRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeMaxStaminaTableMastersRequest> FDescribeMaxStaminaTableMastersRequestPtr;
}