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
#include "../Model/ScopedValue.h"

namespace Gs2::Mission::Request
{
    class FResetCounterByUserIdRequest;

    class GS2MISSION_API FResetCounterByUserIdRequest final : public TSharedFromThis<FResetCounterByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CounterNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> ScopesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FResetCounterByUserIdRequest();
        FResetCounterByUserIdRequest(
            const FResetCounterByUserIdRequest& From
        );
        ~FResetCounterByUserIdRequest() = default;

        TSharedPtr<FResetCounterByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FResetCounterByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FResetCounterByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FResetCounterByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FResetCounterByUserIdRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> Scopes);
        TSharedPtr<FResetCounterByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FResetCounterByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCounterName() const;TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> GetScopes() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FResetCounterByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FResetCounterByUserIdRequest> FResetCounterByUserIdRequestPtr;
}