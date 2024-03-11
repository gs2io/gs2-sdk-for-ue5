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
    class FUpdateBannedRequest;

    class GS2ACCOUNT_API FUpdateBannedRequest final : public TSharedFromThis<FUpdateBannedRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> BannedValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUpdateBannedRequest();
        FUpdateBannedRequest(
            const FUpdateBannedRequest& From
        );
        ~FUpdateBannedRequest() = default;

        TSharedPtr<FUpdateBannedRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateBannedRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateBannedRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUpdateBannedRequest> WithBanned(const TOptional<bool> Banned);
        TSharedPtr<FUpdateBannedRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUpdateBannedRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetBanned() const;
        FString GetBannedString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUpdateBannedRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateBannedRequest, ESPMode::ThreadSafe> FUpdateBannedRequestPtr;
}