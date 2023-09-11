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

namespace Gs2::SkillTree::Request
{
    class FMarkRestrainByUserIdRequest;

    class GS2SKILLTREE_API FMarkRestrainByUserIdRequest final : public TSharedFromThis<FMarkRestrainByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> NodeModelNamesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMarkRestrainByUserIdRequest();
        FMarkRestrainByUserIdRequest(
            const FMarkRestrainByUserIdRequest& From
        );
        ~FMarkRestrainByUserIdRequest() = default;

        TSharedPtr<FMarkRestrainByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMarkRestrainByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMarkRestrainByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMarkRestrainByUserIdRequest> WithNodeModelNames(
            const TSharedPtr<TArray<FString>> NodeModelNames);
        TSharedPtr<FMarkRestrainByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetNodeModelNames() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMarkRestrainByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMarkRestrainByUserIdRequest, ESPMode::ThreadSafe> FMarkRestrainByUserIdRequestPtr;
}