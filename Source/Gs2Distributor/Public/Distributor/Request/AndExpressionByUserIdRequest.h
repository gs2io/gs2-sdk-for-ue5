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
    class FAndExpressionByUserIdRequest;

    class GS2DISTRIBUTOR_API FAndExpressionByUserIdRequest final : public TSharedFromThis<FAndExpressionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ActionsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAndExpressionByUserIdRequest();
        FAndExpressionByUserIdRequest(
            const FAndExpressionByUserIdRequest& From
        );
        ~FAndExpressionByUserIdRequest() = default;

        TSharedPtr<FAndExpressionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAndExpressionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAndExpressionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAndExpressionByUserIdRequest> WithActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> Actions);
        TSharedPtr<FAndExpressionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAndExpressionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetActions() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAndExpressionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAndExpressionByUserIdRequest, ESPMode::ThreadSafe> FAndExpressionByUserIdRequestPtr;
}