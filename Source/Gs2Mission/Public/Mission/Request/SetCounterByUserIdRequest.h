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
#include "../Model/ScopedValue.h"

namespace Gs2::Mission::Request
{
    class FSetCounterByUserIdRequest;

    class GS2MISSION_API FSetCounterByUserIdRequest final : public TSharedFromThis<FSetCounterByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> ValuesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetCounterByUserIdRequest();
        FSetCounterByUserIdRequest(
            const FSetCounterByUserIdRequest& From
        );
        ~FSetCounterByUserIdRequest() = default;

        TSharedPtr<FSetCounterByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetCounterByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetCounterByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FSetCounterByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetCounterByUserIdRequest> WithValues(const TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> Values);
        TSharedPtr<FSetCounterByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetCounterByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> GetValues() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetCounterByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetCounterByUserIdRequest, ESPMode::ThreadSafe> FSetCounterByUserIdRequestPtr;
}