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
#include "SlotModel.h"

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FPropertyFormModelMaster final : public Gs2Object, public TSharedFromThis<FPropertyFormModelMaster>
    {
        TOptional<FString> PropertyFormModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FSlotModel>>> SlotsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPropertyFormModelMaster();
        FPropertyFormModelMaster(
            const FPropertyFormModelMaster& From
        );
        virtual ~FPropertyFormModelMaster() override = default;

        TSharedPtr<FPropertyFormModelMaster> WithPropertyFormModelId(const TOptional<FString> PropertyFormModelId);
        TSharedPtr<FPropertyFormModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FPropertyFormModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FPropertyFormModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPropertyFormModelMaster> WithSlots(const TSharedPtr<TArray<TSharedPtr<FSlotModel>>> Slots);
        TSharedPtr<FPropertyFormModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPropertyFormModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FPropertyFormModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetPropertyFormModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FSlotModel>>> GetSlots() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyFormModelNameFromGrn(const FString Grn);

        static TSharedPtr<FPropertyFormModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPropertyFormModelMaster, ESPMode::ThreadSafe> FPropertyFormModelMasterPtr;
}