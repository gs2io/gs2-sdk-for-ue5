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
#include "Money2/Model/SubscribeTransaction.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzSubscribeTransaction final : public TSharedFromThis<FEzSubscribeTransaction>
	{
        TOptional<FString> ContentNameValue;
        TOptional<FString> StoreValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StatusDetailValue;
        TOptional<int64> ExpiresAtValue;

	public:
        TSharedPtr<FEzSubscribeTransaction> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FEzSubscribeTransaction> WithStore(const TOptional<FString> Store);
        TSharedPtr<FEzSubscribeTransaction> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEzSubscribeTransaction> WithStatusDetail(const TOptional<FString> StatusDetail);
        TSharedPtr<FEzSubscribeTransaction> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetContentName() const;

        TOptional<FString> GetStore() const;

        TOptional<FString> GetTransactionId() const;

        TOptional<FString> GetStatusDetail() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        Gs2::Money2::Model::FSubscribeTransactionPtr ToModel() const;
        static TSharedPtr<FEzSubscribeTransaction> FromModel(Gs2::Money2::Model::FSubscribeTransactionPtr Model);
    };
    typedef TSharedPtr<FEzSubscribeTransaction> FEzSubscribeTransactionPtr;
}