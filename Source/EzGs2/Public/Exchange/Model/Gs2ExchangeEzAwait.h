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
#include "Exchange/Model/Await.h"

namespace Gs2::UE5::Exchange::Model
{
	class EZGS2_API FEzAwait final : public TSharedFromThis<FEzAwait>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> NameValue;
        TOptional<int64> ExchangedAtValue;

	public:
        TSharedPtr<FEzAwait> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzAwait> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FEzAwait> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAwait> WithExchangedAt(const TOptional<int64> ExchangedAt);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetRateName() const;

        TOptional<FString> GetName() const;

        TOptional<int64> GetExchangedAt() const;
        FString GetExchangedAtString() const;

        Gs2::Exchange::Model::FAwaitPtr ToModel() const;
        static TSharedPtr<FEzAwait> FromModel(Gs2::Exchange::Model::FAwaitPtr Model);
    };
    typedef TSharedPtr<FEzAwait> FEzAwaitPtr;
}