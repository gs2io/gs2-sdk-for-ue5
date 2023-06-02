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
#include "DisplayItem.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FShowcase final : public Gs2Object, public TSharedFromThis<FShowcase>
    {
        TOptional<FString> ShowcaseIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> SalesPeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FDisplayItem>>> DisplayItemsValue;

    public:
        FShowcase();
        FShowcase(
            const FShowcase& From
        );
        virtual ~FShowcase() override = default;

        TSharedPtr<FShowcase> WithShowcaseId(const TOptional<FString> ShowcaseId);
        TSharedPtr<FShowcase> WithName(const TOptional<FString> Name);
        TSharedPtr<FShowcase> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FShowcase> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);
        TSharedPtr<FShowcase> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<FDisplayItem>>> DisplayItems);

        TOptional<FString> GetShowcaseId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetSalesPeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FDisplayItem>>> GetDisplayItems() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetShowcaseNameFromGrn(const FString Grn);

        static TSharedPtr<FShowcase> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FShowcase, ESPMode::ThreadSafe> FShowcasePtr;
}