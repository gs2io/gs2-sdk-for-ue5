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
#include "Money2/Model/SubscriptionStatus.h"
#include "Gs2Money2EzSubscribeTransaction.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzSubscriptionStatus final : public TSharedFromThis<FEzSubscriptionStatus>
	{
        TOptional<FString> ContentNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StatusValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>>> DetailValue;

	public:
        TSharedPtr<FEzSubscriptionStatus> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FEzSubscriptionStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzSubscriptionStatus> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FEzSubscriptionStatus> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FEzSubscriptionStatus> WithDetail(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>>> Detail);

        TOptional<FString> GetContentName() const;

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetStatus() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>>> GetDetail() const;

        Gs2::Money2::Model::FSubscriptionStatusPtr ToModel() const;
        static TSharedPtr<FEzSubscriptionStatus> FromModel(Gs2::Money2::Model::FSubscriptionStatusPtr Model);
    };
    typedef TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatusPtr;
}