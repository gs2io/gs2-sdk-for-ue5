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

namespace Gs2::Chat::Request
{
    class FGetCategoryModelMasterRequest;

    class GS2CHAT_API FGetCategoryModelMasterRequest final : public TSharedFromThis<FGetCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> CategoryValue;
        
    public:
        
        FGetCategoryModelMasterRequest();
        FGetCategoryModelMasterRequest(
            const FGetCategoryModelMasterRequest& From
        );
        ~FGetCategoryModelMasterRequest() = default;

        TSharedPtr<FGetCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCategoryModelMasterRequest> WithCategory(const TOptional<int32> Category);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;

        static TSharedPtr<FGetCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCategoryModelMasterRequest> FGetCategoryModelMasterRequestPtr;
}