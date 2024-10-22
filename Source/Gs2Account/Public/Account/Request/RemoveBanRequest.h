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
    class FRemoveBanRequest;

    class GS2ACCOUNT_API FRemoveBanRequest final : public TSharedFromThis<FRemoveBanRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> BanStatusNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRemoveBanRequest();
        FRemoveBanRequest(
            const FRemoveBanRequest& From
        );
        ~FRemoveBanRequest() = default;

        TSharedPtr<FRemoveBanRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRemoveBanRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRemoveBanRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRemoveBanRequest> WithBanStatusName(const TOptional<FString> BanStatusName);
        TSharedPtr<FRemoveBanRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRemoveBanRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetBanStatusName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRemoveBanRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRemoveBanRequest> FRemoveBanRequestPtr;
}