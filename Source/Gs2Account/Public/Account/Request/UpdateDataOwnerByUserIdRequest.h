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
    class FUpdateDataOwnerByUserIdRequest;

    class GS2ACCOUNT_API FUpdateDataOwnerByUserIdRequest final : public TSharedFromThis<FUpdateDataOwnerByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataOwnerNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateDataOwnerByUserIdRequest();
        FUpdateDataOwnerByUserIdRequest(
            const FUpdateDataOwnerByUserIdRequest& From
        );
        ~FUpdateDataOwnerByUserIdRequest() = default;

        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithDataOwnerName(const TOptional<FString> DataOwnerName);
        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateDataOwnerByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataOwnerName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateDataOwnerByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequestPtr;
}