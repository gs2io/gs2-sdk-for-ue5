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

namespace Gs2::Mission::Request
{
    class FIncreaseCounterByUserIdRequest;

    class GS2MISSION_API FIncreaseCounterByUserIdRequest final : public TSharedFromThis<FIncreaseCounterByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIncreaseCounterByUserIdRequest();
        FIncreaseCounterByUserIdRequest(
            const FIncreaseCounterByUserIdRequest& From
        );
        ~FIncreaseCounterByUserIdRequest() = default;

        TSharedPtr<FIncreaseCounterByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncreaseCounterByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIncreaseCounterByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FIncreaseCounterByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FIncreaseCounterByUserIdRequest> WithValue(const TOptional<int64> Value);
        TSharedPtr<FIncreaseCounterByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIncreaseCounterByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncreaseCounterByUserIdRequest, ESPMode::ThreadSafe> FIncreaseCounterByUserIdRequestPtr;
}