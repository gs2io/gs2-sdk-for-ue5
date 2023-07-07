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

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FSimpleItemModel final : public Gs2Object, public TSharedFromThis<FSimpleItemModel>
    {
        TOptional<FString> ItemModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

    public:
        FSimpleItemModel();
        FSimpleItemModel(
            const FSimpleItemModel& From
        );
        virtual ~FSimpleItemModel() override = default;

        TSharedPtr<FSimpleItemModel> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FSimpleItemModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSimpleItemModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetItemModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FSimpleItemModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSimpleItemModel, ESPMode::ThreadSafe> FSimpleItemModelPtr;
}