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

namespace Gs2::Inbox::Request
{
    class FOpenMessageByUserIdRequest;

    class GS2INBOX_API FOpenMessageByUserIdRequest final : public TSharedFromThis<FOpenMessageByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MessageNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FOpenMessageByUserIdRequest();
        FOpenMessageByUserIdRequest(
            const FOpenMessageByUserIdRequest& From
        );
        ~FOpenMessageByUserIdRequest() = default;

        TSharedPtr<FOpenMessageByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FOpenMessageByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FOpenMessageByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FOpenMessageByUserIdRequest> WithMessageName(const TOptional<FString> MessageName);
        TSharedPtr<FOpenMessageByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FOpenMessageByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMessageName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FOpenMessageByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FOpenMessageByUserIdRequest> FOpenMessageByUserIdRequestPtr;
}