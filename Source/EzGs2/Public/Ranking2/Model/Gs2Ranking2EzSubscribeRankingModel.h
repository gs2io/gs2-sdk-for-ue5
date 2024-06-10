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
#include "Ranking2/Model/SubscribeRankingModel.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzSubscribeRankingModel final : public TSharedFromThis<FEzSubscribeRankingModel>
	{
        TOptional<FString> SubscribeRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;

	public:
        TSharedPtr<FEzSubscribeRankingModel> WithSubscribeRankingModelId(const TOptional<FString> SubscribeRankingModelId);
        TSharedPtr<FEzSubscribeRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSubscribeRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSubscribeRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FEzSubscribeRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetSubscribeRankingModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetEntryPeriodEventId() const;

        TOptional<FString> GetAccessPeriodEventId() const;

        Gs2::Ranking2::Model::FSubscribeRankingModelPtr ToModel() const;
        static TSharedPtr<FEzSubscribeRankingModel> FromModel(Gs2::Ranking2::Model::FSubscribeRankingModelPtr Model);
    };
    typedef TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModelPtr;
}