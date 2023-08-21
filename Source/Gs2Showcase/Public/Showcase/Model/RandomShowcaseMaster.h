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
#include "RandomDisplayItemModel.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FRandomShowcaseMaster final : public Gs2Object, public TSharedFromThis<FRandomShowcaseMaster>
    {
        TOptional<FString> ShowcaseIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumNumberOfChoiceValue;
        TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> DisplayItemsValue;
        TOptional<int64> BaseTimestampValue;
        TOptional<int32> ResetIntervalHoursValue;
        TOptional<FString> SalesPeriodEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRandomShowcaseMaster();
        FRandomShowcaseMaster(
            const FRandomShowcaseMaster& From
        );
        virtual ~FRandomShowcaseMaster() override = default;

        TSharedPtr<FRandomShowcaseMaster> WithShowcaseId(const TOptional<FString> ShowcaseId);
        TSharedPtr<FRandomShowcaseMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FRandomShowcaseMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRandomShowcaseMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRandomShowcaseMaster> WithMaximumNumberOfChoice(const TOptional<int32> MaximumNumberOfChoice);
        TSharedPtr<FRandomShowcaseMaster> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> DisplayItems);
        TSharedPtr<FRandomShowcaseMaster> WithBaseTimestamp(const TOptional<int64> BaseTimestamp);
        TSharedPtr<FRandomShowcaseMaster> WithResetIntervalHours(const TOptional<int32> ResetIntervalHours);
        TSharedPtr<FRandomShowcaseMaster> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);
        TSharedPtr<FRandomShowcaseMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRandomShowcaseMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRandomShowcaseMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetShowcaseId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumNumberOfChoice() const;
        FString GetMaximumNumberOfChoiceString() const;
        TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> GetDisplayItems() const;
        TOptional<int64> GetBaseTimestamp() const;
        FString GetBaseTimestampString() const;
        TOptional<int32> GetResetIntervalHours() const;
        FString GetResetIntervalHoursString() const;
        TOptional<FString> GetSalesPeriodEventId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetShowcaseNameFromGrn(const FString Grn);

        static TSharedPtr<FRandomShowcaseMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRandomShowcaseMaster, ESPMode::ThreadSafe> FRandomShowcaseMasterPtr;
}