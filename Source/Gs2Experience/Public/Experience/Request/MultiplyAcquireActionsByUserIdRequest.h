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
#include "../Model/AcquireAction.h"

namespace Gs2::Experience::Request
{
    class FMultiplyAcquireActionsByUserIdRequest;

    class GS2EXPERIENCE_API FMultiplyAcquireActionsByUserIdRequest final : public TSharedFromThis<FMultiplyAcquireActionsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> RateNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMultiplyAcquireActionsByUserIdRequest();
        FMultiplyAcquireActionsByUserIdRequest(
            const FMultiplyAcquireActionsByUserIdRequest& From
        );
        ~FMultiplyAcquireActionsByUserIdRequest() = default;

        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetRateName() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMultiplyAcquireActionsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMultiplyAcquireActionsByUserIdRequest, ESPMode::ThreadSafe> FMultiplyAcquireActionsByUserIdRequestPtr;
}