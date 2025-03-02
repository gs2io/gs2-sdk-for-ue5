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
#include "Core/Gs2Object.h"
#include "SubscribeTransaction.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FSubscriptionStatus final : public Gs2Object, public TSharedFromThis<FSubscriptionStatus>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> ContentNameValue;
        TOptional<FString> StatusValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<TArray<TSharedPtr<FSubscribeTransaction>>> DetailValue;

    public:
        FSubscriptionStatus();
        FSubscriptionStatus(
            const FSubscriptionStatus& From
        );
        virtual ~FSubscriptionStatus() override = default;

        TSharedPtr<FSubscriptionStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscriptionStatus> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FSubscriptionStatus> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FSubscriptionStatus> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FSubscriptionStatus> WithDetail(const TSharedPtr<TArray<TSharedPtr<FSubscribeTransaction>>> Detail);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetContentName() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TSharedPtr<TArray<TSharedPtr<FSubscribeTransaction>>> GetDetail() const;


        static TSharedPtr<FSubscriptionStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscriptionStatus, ESPMode::ThreadSafe> FSubscriptionStatusPtr;
}