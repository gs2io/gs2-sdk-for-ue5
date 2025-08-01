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
    class FCreateCategoryModelMasterRequest;

    class GS2CHAT_API FCreateCategoryModelMasterRequest final : public TSharedFromThis<FCreateCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> CategoryValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> RejectAccessTokenPostValue;
        
    public:
        
        FCreateCategoryModelMasterRequest();
        FCreateCategoryModelMasterRequest(
            const FCreateCategoryModelMasterRequest& From
        );
        ~FCreateCategoryModelMasterRequest() = default;

        TSharedPtr<FCreateCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithCategory(const TOptional<int32> Category);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithRejectAccessTokenPost(const TOptional<FString> RejectAccessTokenPost);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetCategory() const;
        FString GetCategoryString() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetRejectAccessTokenPost() const;

        static TSharedPtr<FCreateCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateCategoryModelMasterRequest> FCreateCategoryModelMasterRequestPtr;
}