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

namespace Gs2::Limit::Request
{
    class FCountUpByUserIdRequest;

    class GS2LIMIT_API FCountUpByUserIdRequest final : public TSharedFromThis<FCountUpByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CountUpValueValue;
        TOptional<int32> MaxValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCountUpByUserIdRequest();
        FCountUpByUserIdRequest(
            const FCountUpByUserIdRequest& From
        );
        ~FCountUpByUserIdRequest() = default;

        TSharedPtr<FCountUpByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCountUpByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCountUpByUserIdRequest> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FCountUpByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FCountUpByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCountUpByUserIdRequest> WithCountUpValue(const TOptional<int32> CountUpValue);
        TSharedPtr<FCountUpByUserIdRequest> WithMaxValue(const TOptional<int32> MaxValue);
        TSharedPtr<FCountUpByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLimitName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCountUpValue() const;
        FString GetCountUpValueString() const;
        TOptional<int32> GetMaxValue() const;
        FString GetMaxValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCountUpByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountUpByUserIdRequest, ESPMode::ThreadSafe> FCountUpByUserIdRequestPtr;
}