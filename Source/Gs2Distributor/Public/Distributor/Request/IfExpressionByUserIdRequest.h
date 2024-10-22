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
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::Distributor::Request
{
    class FIfExpressionByUserIdRequest;

    class GS2DISTRIBUTOR_API FIfExpressionByUserIdRequest final : public TSharedFromThis<FIfExpressionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FVerifyAction> ConditionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> TrueActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FalseActionsValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIfExpressionByUserIdRequest();
        FIfExpressionByUserIdRequest(
            const FIfExpressionByUserIdRequest& From
        );
        ~FIfExpressionByUserIdRequest() = default;

        TSharedPtr<FIfExpressionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIfExpressionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIfExpressionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FIfExpressionByUserIdRequest> WithCondition(const TSharedPtr<Model::FVerifyAction> Condition);
        TSharedPtr<FIfExpressionByUserIdRequest> WithTrueActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> TrueActions);
        TSharedPtr<FIfExpressionByUserIdRequest> WithFalseActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FalseActions);
        TSharedPtr<FIfExpressionByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FIfExpressionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FIfExpressionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FVerifyAction> GetCondition() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetTrueActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetFalseActions() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIfExpressionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIfExpressionByUserIdRequest> FIfExpressionByUserIdRequestPtr;
}