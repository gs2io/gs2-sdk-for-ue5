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

namespace Gs2::Ranking::Request
{
    class FDeleteCategoryModelMasterRequest;

    class GS2RANKING_API FDeleteCategoryModelMasterRequest final : public TSharedFromThis<FDeleteCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        
    public:
        
        FDeleteCategoryModelMasterRequest();
        FDeleteCategoryModelMasterRequest(
            const FDeleteCategoryModelMasterRequest& From
        );
        ~FDeleteCategoryModelMasterRequest() = default;

        TSharedPtr<FDeleteCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteCategoryModelMasterRequest> WithCategoryName(const TOptional<FString> CategoryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;

        static TSharedPtr<FDeleteCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteCategoryModelMasterRequest, ESPMode::ThreadSafe> FDeleteCategoryModelMasterRequestPtr;
}