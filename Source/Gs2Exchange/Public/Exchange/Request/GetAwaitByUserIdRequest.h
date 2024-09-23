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

namespace Gs2::Exchange::Request
{
    class FGetAwaitByUserIdRequest;

    class GS2EXCHANGE_API FGetAwaitByUserIdRequest final : public TSharedFromThis<FGetAwaitByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AwaitNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetAwaitByUserIdRequest();
        FGetAwaitByUserIdRequest(
            const FGetAwaitByUserIdRequest& From
        );
        ~FGetAwaitByUserIdRequest() = default;

        TSharedPtr<FGetAwaitByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetAwaitByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetAwaitByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetAwaitByUserIdRequest> WithAwaitName(const TOptional<FString> AwaitName);
        TSharedPtr<FGetAwaitByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAwaitName() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetAwaitByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetAwaitByUserIdRequest, ESPMode::ThreadSafe> FGetAwaitByUserIdRequestPtr;
}