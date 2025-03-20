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
#include "SimpleItemModel.h"

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FSimpleInventoryModel final : public FGs2Object, public TSharedFromThis<FSimpleInventoryModel>
    {
        TOptional<FString> InventoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FSimpleItemModel>>> SimpleItemModelsValue;

    public:
        FSimpleInventoryModel();
        FSimpleInventoryModel(
            const FSimpleInventoryModel& From
        );
        virtual ~FSimpleInventoryModel() override = default;

        TSharedPtr<FSimpleInventoryModel> WithInventoryModelId(const TOptional<FString> InventoryModelId);
        TSharedPtr<FSimpleInventoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSimpleInventoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSimpleInventoryModel> WithSimpleItemModels(const TSharedPtr<TArray<TSharedPtr<FSimpleItemModel>>> SimpleItemModels);

        TOptional<FString> GetInventoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FSimpleItemModel>>> GetSimpleItemModels() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);

        static TSharedPtr<FSimpleInventoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSimpleInventoryModel, ESPMode::ThreadSafe> FSimpleInventoryModelPtr;
}