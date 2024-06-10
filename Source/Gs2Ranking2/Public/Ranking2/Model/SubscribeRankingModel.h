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
    class GS2RANKING2_API FSubscribeRankingModel final : public Gs2Object, public TSharedFromThis<FSubscribeRankingModel>
    {
        TOptional<FString> SubscribeRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;

    public:
        FSubscribeRankingModel();
        FSubscribeRankingModel(
            const FSubscribeRankingModel& From
        );
        virtual ~FSubscribeRankingModel() override = default;

        TSharedPtr<FSubscribeRankingModel> WithSubscribeRankingModelId(const TOptional<FString> SubscribeRankingModelId);
        TSharedPtr<FSubscribeRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSubscribeRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSubscribeRankingModel> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FSubscribeRankingModel> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FSubscribeRankingModel> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FSubscribeRankingModel> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FSubscribeRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FSubscribeRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetSubscribeRankingModelId() const;
        TOptional<FString> GetName() const;
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

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FSubscribeRankingModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeRankingModel, ESPMode::ThreadSafe> FSubscribeRankingModelPtr;
}