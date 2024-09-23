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
#include "../Model/VerifyAction.h"

namespace Gs2::Distributor::Request
{
    class FOrExpressionByUserIdRequest;

    class GS2DISTRIBUTOR_API FOrExpressionByUserIdRequest final : public TSharedFromThis<FOrExpressionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ActionsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FOrExpressionByUserIdRequest();
        FOrExpressionByUserIdRequest(
            const FOrExpressionByUserIdRequest& From
        );
        ~FOrExpressionByUserIdRequest() = default;

        TSharedPtr<FOrExpressionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FOrExpressionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FOrExpressionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FOrExpressionByUserIdRequest> WithActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> Actions);
        TSharedPtr<FOrExpressionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FOrExpressionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetActions() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FOrExpressionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FOrExpressionByUserIdRequest, ESPMode::ThreadSafe> FOrExpressionByUserIdRequestPtr;
}