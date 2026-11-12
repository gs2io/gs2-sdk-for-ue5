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

namespace Gs2::Account::Request
{
    class FCancelDeletionRequest;

    class GS2ACCOUNT_API FCancelDeletionRequest final : public TSharedFromThis<FCancelDeletionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCancelDeletionRequest();
        FCancelDeletionRequest(
            const FCancelDeletionRequest& From
        );
        ~FCancelDeletionRequest() = default;

        TSharedPtr<FCancelDeletionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCancelDeletionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCancelDeletionRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCancelDeletionRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FCancelDeletionRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCancelDeletionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCancelDeletionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCancelDeletionRequest> FCancelDeletionRequestPtr;
}