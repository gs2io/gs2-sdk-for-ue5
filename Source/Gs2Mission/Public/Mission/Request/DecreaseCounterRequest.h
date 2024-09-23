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
    class FDecreaseCounterRequest;

    class GS2MISSION_API FDecreaseCounterRequest final : public TSharedFromThis<FDecreaseCounterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseCounterRequest();
        FDecreaseCounterRequest(
            const FDecreaseCounterRequest& From
        );
        ~FDecreaseCounterRequest() = default;

        TSharedPtr<FDecreaseCounterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseCounterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseCounterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FDecreaseCounterRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDecreaseCounterRequest> WithValue(const TOptional<int64> Value);
        TSharedPtr<FDecreaseCounterRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseCounterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseCounterRequest, ESPMode::ThreadSafe> FDecreaseCounterRequestPtr;
}