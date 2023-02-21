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
    class FDeleteAwaitByUserIdRequest;

    class GS2EXCHANGE_API FDeleteAwaitByUserIdRequest final : public TSharedFromThis<FDeleteAwaitByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AwaitNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteAwaitByUserIdRequest();
        FDeleteAwaitByUserIdRequest(
            const FDeleteAwaitByUserIdRequest& From
        );
        ~FDeleteAwaitByUserIdRequest() = default;

        TSharedPtr<FDeleteAwaitByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteAwaitByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteAwaitByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteAwaitByUserIdRequest> WithAwaitName(const TOptional<FString> AwaitName);
        TSharedPtr<FDeleteAwaitByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAwaitName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteAwaitByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteAwaitByUserIdRequest, ESPMode::ThreadSafe> FDeleteAwaitByUserIdRequestPtr;
}