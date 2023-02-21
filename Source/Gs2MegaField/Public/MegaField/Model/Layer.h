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

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FLayer final : public TSharedFromThis<FLayer>
    {
        TOptional<FString> LayerIdValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TOptional<int32> NumberOfMinEntriesValue;
        TOptional<int32> NumberOfMaxEntriesValue;
        TOptional<int64> CreatedAtValue;

    public:
        FLayer();
        FLayer(
            const FLayer& From
        );
        ~FLayer() = default;

        TSharedPtr<FLayer> WithLayerId(const TOptional<FString> LayerId);
        TSharedPtr<FLayer> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FLayer> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FLayer> WithNumberOfMinEntries(const TOptional<int32> NumberOfMinEntries);
        TSharedPtr<FLayer> WithNumberOfMaxEntries(const TOptional<int32> NumberOfMaxEntries);
        TSharedPtr<FLayer> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetLayerId() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TOptional<int32> GetNumberOfMinEntries() const;
        FString GetNumberOfMinEntriesString() const;
        TOptional<int32> GetNumberOfMaxEntries() const;
        FString GetNumberOfMaxEntriesString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetAreaModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetLayerModelNameFromGrn(const FString Grn);

        static TSharedPtr<FLayer> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLayer, ESPMode::ThreadSafe> FLayerPtr;
}