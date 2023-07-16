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
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FRandomDisplayItemModel final : public Gs2Object, public TSharedFromThis<FRandomDisplayItemModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int32> StockValue;
        TOptional<int32> WeightValue;

    public:
        FRandomDisplayItemModel();
        FRandomDisplayItemModel(
            const FRandomDisplayItemModel& From
        );
        virtual ~FRandomDisplayItemModel() override = default;

        TSharedPtr<FRandomDisplayItemModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRandomDisplayItemModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRandomDisplayItemModel> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FRandomDisplayItemModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FRandomDisplayItemModel> WithStock(const TOptional<int32> Stock);
        TSharedPtr<FRandomDisplayItemModel> WithWeight(const TOptional<int32> Weight);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;
        TOptional<int32> GetStock() const;
        FString GetStockString() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FRandomDisplayItemModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRandomDisplayItemModel, ESPMode::ThreadSafe> FRandomDisplayItemModelPtr;
}