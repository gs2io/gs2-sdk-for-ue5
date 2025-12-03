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
#include "Limit/Model/LimitModel.h"

namespace Gs2::UE5::Limit::Model
{
	class EZGS2_API FEzLimitModel final : public TSharedFromThis<FEzLimitModel>
	{
        TOptional<FString> LimitModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<int64> AnchorTimestampValue;
        TOptional<int32> DaysValue;

	public:
        TSharedPtr<FEzLimitModel> WithLimitModelId(const TOptional<FString> LimitModelId);
        TSharedPtr<FEzLimitModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzLimitModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzLimitModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FEzLimitModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FEzLimitModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FEzLimitModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FEzLimitModel> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FEzLimitModel> WithDays(const TOptional<int32> Days);

        TOptional<FString> GetLimitModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetResetType() const;

        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;

        TOptional<FString> GetResetDayOfWeek() const;

        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        TOptional<int64> GetAnchorTimestamp() const;
        FString GetAnchorTimestampString() const;

        TOptional<int32> GetDays() const;
        FString GetDaysString() const;

        Gs2::Limit::Model::FLimitModelPtr ToModel() const;
        static TSharedPtr<FEzLimitModel> FromModel(Gs2::Limit::Model::FLimitModelPtr Model);
    };
    typedef TSharedPtr<FEzLimitModel> FEzLimitModelPtr;
}