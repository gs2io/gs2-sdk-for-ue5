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

namespace Gs2::Account::Request
{
    class FDeleteAccountRequest;

    class GS2ACCOUNT_API FDeleteAccountRequest final : public TSharedFromThis<FDeleteAccountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        
    public:
        
        FDeleteAccountRequest();
        FDeleteAccountRequest(
            const FDeleteAccountRequest& From
        );
        ~FDeleteAccountRequest() = default;

        TSharedPtr<FDeleteAccountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteAccountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteAccountRequest> WithUserId(const TOptional<FString> UserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;

        static TSharedPtr<FDeleteAccountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteAccountRequest, ESPMode::ThreadSafe> FDeleteAccountRequestPtr;
}