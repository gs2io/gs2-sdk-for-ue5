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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FDisplayItemMaster final : public FGs2Object, public TSharedFromThis<FDisplayItemMaster>
    {
        TOptional<FString> DisplayItemIdValue;
        TOptional<FString> TypeValue;
        TOptional<FString> SalesItemNameValue;
        TOptional<FString> SalesItemGroupNameValue;
        TOptional<FString> SalesPeriodEventIdValue;
        TOptional<int64> RevisionValue;

    public:
        FDisplayItemMaster();
        FDisplayItemMaster(
            const FDisplayItemMaster& From
        );
        virtual ~FDisplayItemMaster() override = default;

        TSharedPtr<FDisplayItemMaster> WithDisplayItemId(const TOptional<FString> DisplayItemId);
        TSharedPtr<FDisplayItemMaster> WithType(const TOptional<FString> Type);
        TSharedPtr<FDisplayItemMaster> WithSalesItemName(const TOptional<FString> SalesItemName);
        TSharedPtr<FDisplayItemMaster> WithSalesItemGroupName(const TOptional<FString> SalesItemGroupName);
        TSharedPtr<FDisplayItemMaster> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);
        TSharedPtr<FDisplayItemMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetDisplayItemId() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetSalesItemName() const;
        TOptional<FString> GetSalesItemGroupName() const;
        TOptional<FString> GetSalesPeriodEventId() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;


        static TSharedPtr<FDisplayItemMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDisplayItemMaster, ESPMode::ThreadSafe> FDisplayItemMasterPtr;
}