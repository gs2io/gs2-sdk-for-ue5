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
    class GS2FORMATION_API FFormModelMaster final : public Gs2Object, public TSharedFromThis<FFormModelMaster>
    {
        TOptional<FString> FormModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FSlotModel>>> SlotsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FFormModelMaster();
        FFormModelMaster(
            const FFormModelMaster& From
        );
        virtual ~FFormModelMaster() override = default;

        TSharedPtr<FFormModelMaster> WithFormModelId(const TOptional<FString> FormModelId);
        TSharedPtr<FFormModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FFormModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FFormModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FFormModelMaster> WithSlots(const TSharedPtr<TArray<TSharedPtr<FSlotModel>>> Slots);
        TSharedPtr<FFormModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FFormModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FFormModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetFormModelId() const;
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
        static TOptional<FString> GetFormModelNameFromGrn(const FString Grn);

        static TSharedPtr<FFormModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFormModelMaster, ESPMode::ThreadSafe> FFormModelMasterPtr;
}