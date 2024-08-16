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
    class FUpdateTakeOverByUserIdRequest;

    class GS2ACCOUNT_API FUpdateTakeOverByUserIdRequest final : public TSharedFromThis<FUpdateTakeOverByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> OldPasswordValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateTakeOverByUserIdRequest();
        FUpdateTakeOverByUserIdRequest(
            const FUpdateTakeOverByUserIdRequest& From
        );
        ~FUpdateTakeOverByUserIdRequest() = default;

        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithOldPassword(const TOptional<FString> OldPassword);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateTakeOverByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetOldPassword() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateTakeOverByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateTakeOverByUserIdRequest> FUpdateTakeOverByUserIdRequestPtr;
}