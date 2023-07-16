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
    class GS2SHOWCASE_API FRandomDisplayItem final : public Gs2Object, public TSharedFromThis<FRandomDisplayItem>
    {
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int32> CurrentPurchaseCountValue;
        TOptional<int32> MaximumPurchaseCountValue;

    public:
        FRandomDisplayItem();
        FRandomDisplayItem(
            const FRandomDisplayItem& From
        );
        virtual ~FRandomDisplayItem() override = default;

        TSharedPtr<FRandomDisplayItem> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FRandomDisplayItem> WithName(const TOptional<FString> Name);
        TSharedPtr<FRandomDisplayItem> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRandomDisplayItem> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FRandomDisplayItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FRandomDisplayItem> WithCurrentPurchaseCount(const TOptional<int32> CurrentPurchaseCount);
        TSharedPtr<FRandomDisplayItem> WithMaximumPurchaseCount(const TOptional<int32> MaximumPurchaseCount);

        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;
        TOptional<int32> GetCurrentPurchaseCount() const;
        FString GetCurrentPurchaseCountString() const;
        TOptional<int32> GetMaximumPurchaseCount() const;
        FString GetMaximumPurchaseCountString() const;


        static TSharedPtr<FRandomDisplayItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRandomDisplayItem, ESPMode::ThreadSafe> FRandomDisplayItemPtr;
}