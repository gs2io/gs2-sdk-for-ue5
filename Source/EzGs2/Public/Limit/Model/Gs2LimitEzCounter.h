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
#include "Limit/Model/Counter.h"

namespace Gs2::UE5::Limit::Model
{
	class EZGS2_API FEzCounter final : public TSharedFromThis<FEzCounter>
	{
        TOptional<FString> CounterIdValue;
        TOptional<FString> LimitNameValue;
        TOptional<FString> NameValue;
        TOptional<int32> CountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzCounter> WithCounterId(const TOptional<FString> CounterId);
        TSharedPtr<FEzCounter> WithLimitName(const TOptional<FString> LimitName);
        TSharedPtr<FEzCounter> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzCounter> WithCount(const TOptional<int32> Count);
        TSharedPtr<FEzCounter> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEzCounter> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetCounterId() const;

        TOptional<FString> GetLimitName() const;

        TOptional<FString> GetName() const;

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Limit::Model::FCounterPtr ToModel() const;
        static TSharedPtr<FEzCounter> FromModel(Gs2::Limit::Model::FCounterPtr Model);
    };
    typedef TSharedPtr<FEzCounter> FEzCounterPtr;
}