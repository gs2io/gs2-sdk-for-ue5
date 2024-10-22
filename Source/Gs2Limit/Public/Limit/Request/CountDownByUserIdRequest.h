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

namespace Gs2::Limit::Request
{
    class FCountDownByUserIdRequest;

    class GS2LIMIT_API FCountDownByUserIdRequest final : public TSharedFromThis<FCountDownByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CountDownValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCountDownByUserIdRequest();
        FCountDownByUserIdRequest(
            const FCountDownByUserIdRequest& From
        );
        ~FCountDownByUserIdRequest() = default;

        TSharedPtr<FCountDownByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCountDownByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCountDownByUserIdRequest> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FCountDownByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FCountDownByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCountDownByUserIdRequest> WithCountDownValue(const TOptional<int32> CountDownValue);
        TSharedPtr<FCountDownByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCountDownByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLimitName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCountDownValue() const;
        FString GetCountDownValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCountDownByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountDownByUserIdRequest> FCountDownByUserIdRequestPtr;
}