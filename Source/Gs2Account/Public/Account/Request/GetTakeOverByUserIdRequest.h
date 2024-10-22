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
    class FGetTakeOverByUserIdRequest;

    class GS2ACCOUNT_API FGetTakeOverByUserIdRequest final : public TSharedFromThis<FGetTakeOverByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetTakeOverByUserIdRequest();
        FGetTakeOverByUserIdRequest(
            const FGetTakeOverByUserIdRequest& From
        );
        ~FGetTakeOverByUserIdRequest() = default;

        TSharedPtr<FGetTakeOverByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetTakeOverByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetTakeOverByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetTakeOverByUserIdRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FGetTakeOverByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetTakeOverByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetTakeOverByUserIdRequest> FGetTakeOverByUserIdRequestPtr;
}