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

namespace Gs2::SkillTree::Request
{
    class FDescribeNodeModelsRequest;

    class GS2SKILLTREE_API FDescribeNodeModelsRequest final : public TSharedFromThis<FDescribeNodeModelsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        
    public:
        
        FDescribeNodeModelsRequest();
        FDescribeNodeModelsRequest(
            const FDescribeNodeModelsRequest& From
        );
        ~FDescribeNodeModelsRequest() = default;

        TSharedPtr<FDescribeNodeModelsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeNodeModelsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;

        static TSharedPtr<FDescribeNodeModelsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeNodeModelsRequest> FDescribeNodeModelsRequestPtr;
}