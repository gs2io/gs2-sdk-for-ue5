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
    class FMarkRestrainRequest;

    class GS2SKILLTREE_API FMarkRestrainRequest final : public TSharedFromThis<FMarkRestrainRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<FString>> NodeModelNamesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMarkRestrainRequest();
        FMarkRestrainRequest(
            const FMarkRestrainRequest& From
        );
        ~FMarkRestrainRequest() = default;

        TSharedPtr<FMarkRestrainRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMarkRestrainRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMarkRestrainRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FMarkRestrainRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FMarkRestrainRequest> WithNodeModelNames(
            const TSharedPtr<TArray<FString>> NodeModelNames);
        TSharedPtr<FMarkRestrainRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<FString>> GetNodeModelNames() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMarkRestrainRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMarkRestrainRequest> FMarkRestrainRequestPtr;
}