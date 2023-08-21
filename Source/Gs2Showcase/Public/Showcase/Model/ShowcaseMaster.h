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
#include "DisplayItemMaster.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FShowcaseMaster final : public Gs2Object, public TSharedFromThis<FShowcaseMaster>
    {
        TOptional<FString> ShowcaseIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> SalesPeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FDisplayItemMaster>>> DisplayItemsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FShowcaseMaster();
        FShowcaseMaster(
            const FShowcaseMaster& From
        );
        virtual ~FShowcaseMaster() override = default;

        TSharedPtr<FShowcaseMaster> WithShowcaseId(const TOptional<FString> ShowcaseId);
        TSharedPtr<FShowcaseMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FShowcaseMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FShowcaseMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FShowcaseMaster> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);
        TSharedPtr<FShowcaseMaster> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<FDisplayItemMaster>>> DisplayItems);
        TSharedPtr<FShowcaseMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FShowcaseMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FShowcaseMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetShowcaseId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetSalesPeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FDisplayItemMaster>>> GetDisplayItems() const;
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

        static TSharedPtr<FShowcaseMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FShowcaseMaster, ESPMode::ThreadSafe> FShowcaseMasterPtr;
}