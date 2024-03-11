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
    class FDecreaseCounterByUserIdRequest;

    class GS2MISSION_API FDecreaseCounterByUserIdRequest final : public TSharedFromThis<FDecreaseCounterByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseCounterByUserIdRequest();
        FDecreaseCounterByUserIdRequest(
            const FDecreaseCounterByUserIdRequest& From
        );
        ~FDecreaseCounterByUserIdRequest() = default;

        TSharedPtr<FDecreaseCounterByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithValue(const TOptional<int64> Value);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDecreaseCounterByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseCounterByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseCounterByUserIdRequest, ESPMode::ThreadSafe> FDecreaseCounterByUserIdRequestPtr;
}