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
    class FCreateTakeOverByUserIdRequest;

    class GS2ACCOUNT_API FCreateTakeOverByUserIdRequest final : public TSharedFromThis<FCreateTakeOverByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateTakeOverByUserIdRequest();
        FCreateTakeOverByUserIdRequest(
            const FCreateTakeOverByUserIdRequest& From
        );
        ~FCreateTakeOverByUserIdRequest() = default;

        TSharedPtr<FCreateTakeOverByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FCreateTakeOverByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateTakeOverByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateTakeOverByUserIdRequest, ESPMode::ThreadSafe> FCreateTakeOverByUserIdRequestPtr;
}