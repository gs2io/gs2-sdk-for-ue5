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
    class FGetCounterByUserIdRequest;

    class GS2LIMIT_API FGetCounterByUserIdRequest final : public TSharedFromThis<FGetCounterByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetCounterByUserIdRequest();
        FGetCounterByUserIdRequest(
            const FGetCounterByUserIdRequest& From
        );
        ~FGetCounterByUserIdRequest() = default;

        TSharedPtr<FGetCounterByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCounterByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCounterByUserIdRequest> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FGetCounterByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetCounterByUserIdRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FGetCounterByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLimitName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetCounterByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCounterByUserIdRequest, ESPMode::ThreadSafe> FGetCounterByUserIdRequestPtr;
}