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
#include "Position.h"
#include "Vector.h"

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FSpatial final : public TSharedFromThis<FSpatial>
    {
        TOptional<FString> SpatialIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<FPosition> PositionValue;
        TSharedPtr<FVector> VectorValue;
        TOptional<float> RValue;
        TOptional<int64> LastSyncAtValue;
        TOptional<int64> CreatedAtValue;

    public:
        FSpatial();
        FSpatial(
            const FSpatial& From
        );
        ~FSpatial() = default;

        TSharedPtr<FSpatial> WithSpatialId(const TOptional<FString> SpatialId);
        TSharedPtr<FSpatial> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSpatial> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FSpatial> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FSpatial> WithPosition(const TSharedPtr<FPosition> Position);
        TSharedPtr<FSpatial> WithVector(const TSharedPtr<FVector> Vector);
        TSharedPtr<FSpatial> WithR(const TOptional<float> R);
        TSharedPtr<FSpatial> WithLastSyncAt(const TOptional<int64> LastSyncAt);
        TSharedPtr<FSpatial> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetSpatialId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<FPosition> GetPosition() const;
        TSharedPtr<FVector> GetVector() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<int64> GetLastSyncAt() const;
        FString GetLastSyncAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetAreaModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetLayerModelNameFromGrn(const FString Grn);

        static TSharedPtr<FSpatial> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSpatial, ESPMode::ThreadSafe> FSpatialPtr;
}