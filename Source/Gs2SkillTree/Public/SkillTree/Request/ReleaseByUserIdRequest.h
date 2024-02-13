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
#include "../Model/Config.h"

namespace Gs2::SkillTree::Request
{
    class FReleaseByUserIdRequest;

    class GS2SKILLTREE_API FReleaseByUserIdRequest final : public TSharedFromThis<FReleaseByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<FString>> NodeModelNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReleaseByUserIdRequest();
        FReleaseByUserIdRequest(
            const FReleaseByUserIdRequest& From
        );
        ~FReleaseByUserIdRequest() = default;

        TSharedPtr<FReleaseByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReleaseByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReleaseByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReleaseByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FReleaseByUserIdRequest> WithNodeModelNames(
            const TSharedPtr<TArray<FString>> NodeModelNames);
        TSharedPtr<FReleaseByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReleaseByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<FString>> GetNodeModelNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReleaseByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReleaseByUserIdRequest, ESPMode::ThreadSafe> FReleaseByUserIdRequestPtr;
}