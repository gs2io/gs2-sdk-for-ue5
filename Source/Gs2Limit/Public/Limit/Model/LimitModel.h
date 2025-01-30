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

namespace Gs2::Limit::Model
{
    class GS2LIMIT_API FLimitModel final : public Gs2Object, public TSharedFromThis<FLimitModel>
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
        FLimitModel();
        FLimitModel(
            const FLimitModel& From
        );
        virtual ~FLimitModel() override = default;

        TSharedPtr<FLimitModel> WithLimitModelId(const TOptional<FString> LimitModelId);
        TSharedPtr<FLimitModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FLimitModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FLimitModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FLimitModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FLimitModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FLimitModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FLimitModel> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FLimitModel> WithDays(const TOptional<int32> Days);

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

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetLimitNameFromGrn(const FString Grn);

        static TSharedPtr<FLimitModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLimitModel, ESPMode::ThreadSafe> FLimitModelPtr;
}