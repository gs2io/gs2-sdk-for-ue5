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

namespace Gs2::Inbox::Request
{
    class FDeleteReceivedByUserIdRequest;

    class GS2INBOX_API FDeleteReceivedByUserIdRequest final : public TSharedFromThis<FDeleteReceivedByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteReceivedByUserIdRequest();
        FDeleteReceivedByUserIdRequest(
            const FDeleteReceivedByUserIdRequest& From
        );
        ~FDeleteReceivedByUserIdRequest() = default;

        TSharedPtr<FDeleteReceivedByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteReceivedByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteReceivedByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteReceivedByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteReceivedByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteReceivedByUserIdRequest, ESPMode::ThreadSafe> FDeleteReceivedByUserIdRequestPtr;
}