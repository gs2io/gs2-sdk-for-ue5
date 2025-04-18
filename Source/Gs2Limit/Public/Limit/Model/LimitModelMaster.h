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
    class GS2LIMIT_API FLimitModelMaster final : public FGs2Object, public TSharedFromThis<FLimitModelMaster>
    {
        TOptional<FString> LimitModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<int64> AnchorTimestampValue;
        TOptional<int32> DaysValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FLimitModelMaster();
        FLimitModelMaster(
            const FLimitModelMaster& From
        );
        virtual ~FLimitModelMaster() override = default;

        TSharedPtr<FLimitModelMaster> WithLimitModelId(const TOptional<FString> LimitModelId);
        TSharedPtr<FLimitModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FLimitModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FLimitModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FLimitModelMaster> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FLimitModelMaster> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FLimitModelMaster> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FLimitModelMaster> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FLimitModelMaster> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FLimitModelMaster> WithDays(const TOptional<int32> Days);
        TSharedPtr<FLimitModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FLimitModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FLimitModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetLimitModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
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
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetLimitNameFromGrn(const FString Grn);

        static TSharedPtr<FLimitModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLimitModelMaster, ESPMode::ThreadSafe> FLimitModelMasterPtr;
}