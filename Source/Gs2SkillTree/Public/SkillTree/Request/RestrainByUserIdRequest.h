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
    class FRestrainByUserIdRequest;

    class GS2SKILLTREE_API FRestrainByUserIdRequest final : public TSharedFromThis<FRestrainByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<FString>> NodeModelNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRestrainByUserIdRequest();
        FRestrainByUserIdRequest(
            const FRestrainByUserIdRequest& From
        );
        ~FRestrainByUserIdRequest() = default;

        TSharedPtr<FRestrainByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRestrainByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRestrainByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRestrainByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FRestrainByUserIdRequest> WithNodeModelNames(
            const TSharedPtr<TArray<FString>> NodeModelNames);
        TSharedPtr<FRestrainByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FRestrainByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRestrainByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<FString>> GetNodeModelNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRestrainByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRestrainByUserIdRequest> FRestrainByUserIdRequestPtr;
}