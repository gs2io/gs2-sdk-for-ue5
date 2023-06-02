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
#include "LayerModel.h"

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FAreaModel final : public Gs2Object, public TSharedFromThis<FAreaModel>
    {
        TOptional<FString> AreaModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FLayerModel>>> LayerModelsValue;

    public:
        FAreaModel();
        FAreaModel(
            const FAreaModel& From
        );
        virtual ~FAreaModel() override = default;

        TSharedPtr<FAreaModel> WithAreaModelId(const TOptional<FString> AreaModelId);
        TSharedPtr<FAreaModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FAreaModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FAreaModel> WithLayerModels(const TSharedPtr<TArray<TSharedPtr<FLayerModel>>> LayerModels);

        TOptional<FString> GetAreaModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FLayerModel>>> GetLayerModels() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetAreaModelNameFromGrn(const FString Grn);

        static TSharedPtr<FAreaModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAreaModel, ESPMode::ThreadSafe> FAreaModelPtr;
}