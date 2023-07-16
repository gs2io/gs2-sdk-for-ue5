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
    class GS2SHOWCASE_API FRandomShowcase final : public Gs2Object, public TSharedFromThis<FRandomShowcase>
    {
        TOptional<FString> RandomShowcaseIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumNumberOfChoiceValue;
        TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> DisplayItemsValue;
        TOptional<int64> BaseTimestampValue;
        TOptional<int32> ResetIntervalHoursValue;
        TOptional<FString> SalesPeriodEventIdValue;

    public:
        FRandomShowcase();
        FRandomShowcase(
            const FRandomShowcase& From
        );
        virtual ~FRandomShowcase() override = default;

        TSharedPtr<FRandomShowcase> WithRandomShowcaseId(const TOptional<FString> RandomShowcaseId);
        TSharedPtr<FRandomShowcase> WithName(const TOptional<FString> Name);
        TSharedPtr<FRandomShowcase> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRandomShowcase> WithMaximumNumberOfChoice(const TOptional<int32> MaximumNumberOfChoice);
        TSharedPtr<FRandomShowcase> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> DisplayItems);
        TSharedPtr<FRandomShowcase> WithBaseTimestamp(const TOptional<int64> BaseTimestamp);
        TSharedPtr<FRandomShowcase> WithResetIntervalHours(const TOptional<int32> ResetIntervalHours);
        TSharedPtr<FRandomShowcase> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetRandomShowcaseId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumNumberOfChoice() const;
        FString GetMaximumNumberOfChoiceString() const;
        TSharedPtr<TArray<TSharedPtr<FRandomDisplayItemModel>>> GetDisplayItems() const;
        TOptional<int64> GetBaseTimestamp() const;
        FString GetBaseTimestampString() const;
        TOptional<int32> GetResetIntervalHours() const;
        FString GetResetIntervalHoursString() const;
        TOptional<FString> GetSalesPeriodEventId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetShowcaseNameFromGrn(const FString Grn);

        static TSharedPtr<FRandomShowcase> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRandomShowcase, ESPMode::ThreadSafe> FRandomShowcasePtr;
}