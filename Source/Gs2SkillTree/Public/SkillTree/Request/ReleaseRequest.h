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
#include "../Model/Config.h"

namespace Gs2::SkillTree::Request
{
    class FReleaseRequest;

    class GS2SKILLTREE_API FReleaseRequest final : public TSharedFromThis<FReleaseRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<FString>> NodeModelNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReleaseRequest();
        FReleaseRequest(
            const FReleaseRequest& From
        );
        ~FReleaseRequest() = default;

        TSharedPtr<FReleaseRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReleaseRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReleaseRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FReleaseRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FReleaseRequest> WithNodeModelNames(
            const TSharedPtr<TArray<FString>> NodeModelNames);
        TSharedPtr<FReleaseRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReleaseRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<FString>> GetNodeModelNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReleaseRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReleaseRequest> FReleaseRequestPtr;
}