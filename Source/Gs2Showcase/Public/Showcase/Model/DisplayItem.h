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
#include "SalesItem.h"
#include "SalesItemGroup.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FDisplayItem final : public Gs2Object, public TSharedFromThis<FDisplayItem>
    {
        TOptional<FString> DisplayItemIdValue;
        TOptional<FString> TypeValue;
        TSharedPtr<FSalesItem> SalesItemValue;
        TSharedPtr<FSalesItemGroup> SalesItemGroupValue;
        TOptional<FString> SalesPeriodEventIdValue;

    public:
        FDisplayItem();
        FDisplayItem(
            const FDisplayItem& From
        );
        virtual ~FDisplayItem() override = default;

        TSharedPtr<FDisplayItem> WithDisplayItemId(const TOptional<FString> DisplayItemId);
        TSharedPtr<FDisplayItem> WithType(const TOptional<FString> Type);
        TSharedPtr<FDisplayItem> WithSalesItem(const TSharedPtr<FSalesItem> SalesItem);
        TSharedPtr<FDisplayItem> WithSalesItemGroup(const TSharedPtr<FSalesItemGroup> SalesItemGroup);
        TSharedPtr<FDisplayItem> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetDisplayItemId() const;
        TOptional<FString> GetType() const;
        TSharedPtr<FSalesItem> GetSalesItem() const;
        TSharedPtr<FSalesItemGroup> GetSalesItemGroup() const;
        TOptional<FString> GetSalesPeriodEventId() const;


        static TSharedPtr<FDisplayItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDisplayItem, ESPMode::ThreadSafe> FDisplayItemPtr;
}