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

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FSubscribeRankingModelMaster final : public FGs2Object, public TSharedFromThis<FSubscribeRankingModelMaster>
    {
        TOptional<FString> SubscribeRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSubscribeRankingModelMaster();
        FSubscribeRankingModelMaster(
            const FSubscribeRankingModelMaster& From
        );
        virtual ~FSubscribeRankingModelMaster() override = default;

        TSharedPtr<FSubscribeRankingModelMaster> WithSubscribeRankingModelId(const TOptional<FString> SubscribeRankingModelId);
        TSharedPtr<FSubscribeRankingModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FSubscribeRankingModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FSubscribeRankingModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSubscribeRankingModelMaster> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FSubscribeRankingModelMaster> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FSubscribeRankingModelMaster> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FSubscribeRankingModelMaster> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FSubscribeRankingModelMaster> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FSubscribeRankingModelMaster> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FSubscribeRankingModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSubscribeRankingModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSubscribeRankingModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSubscribeRankingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FSubscribeRankingModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeRankingModelMaster, ESPMode::ThreadSafe> FSubscribeRankingModelMasterPtr;
}