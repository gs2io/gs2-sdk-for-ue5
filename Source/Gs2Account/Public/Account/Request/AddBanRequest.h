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
#include "../Model/BanStatus.h"

namespace Gs2::Account::Request
{
    class FAddBanRequest;

    class GS2ACCOUNT_API FAddBanRequest final : public TSharedFromThis<FAddBanRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FBanStatus> BanStatusValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAddBanRequest();
        FAddBanRequest(
            const FAddBanRequest& From
        );
        ~FAddBanRequest() = default;

        TSharedPtr<FAddBanRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAddBanRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAddBanRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAddBanRequest> WithBanStatus(const TSharedPtr<Model::FBanStatus> BanStatus);
        TSharedPtr<FAddBanRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAddBanRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FBanStatus> GetBanStatus() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAddBanRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddBanRequest, ESPMode::ThreadSafe> FAddBanRequestPtr;
}