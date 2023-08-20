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
#include "BigItemModel.h"

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FBigInventoryModel final : public Gs2Object, public TSharedFromThis<FBigInventoryModel>
    {
        TOptional<FString> InventoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FBigItemModel>>> BigItemModelsValue;

    public:
        FBigInventoryModel();
        FBigInventoryModel(
            const FBigInventoryModel& From
        );
        virtual ~FBigInventoryModel() override = default;

        TSharedPtr<FBigInventoryModel> WithInventoryModelId(const TOptional<FString> InventoryModelId);
        TSharedPtr<FBigInventoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FBigInventoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBigInventoryModel> WithBigItemModels(const TSharedPtr<TArray<TSharedPtr<FBigItemModel>>> BigItemModels);

        TOptional<FString> GetInventoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FBigItemModel>>> GetBigItemModels() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);

        static TSharedPtr<FBigInventoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBigInventoryModel, ESPMode::ThreadSafe> FBigInventoryModelPtr;
}