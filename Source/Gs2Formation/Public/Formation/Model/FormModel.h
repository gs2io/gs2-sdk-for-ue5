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
    class GS2FORMATION_API FFormModel final : public Gs2Object, public TSharedFromThis<FFormModel>
    {
        TOptional<FString> FormModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FSlotModel>>> SlotsValue;

    public:
        FFormModel();
        FFormModel(
            const FFormModel& From
        );
        virtual ~FFormModel() override = default;

        TSharedPtr<FFormModel> WithFormModelId(const TOptional<FString> FormModelId);
        TSharedPtr<FFormModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FFormModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FFormModel> WithSlots(const TSharedPtr<TArray<TSharedPtr<FSlotModel>>> Slots);

        TOptional<FString> GetFormModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FSlotModel>>> GetSlots() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMoldModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetFormModelNameFromGrn(const FString Grn);

        static TSharedPtr<FFormModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFormModel, ESPMode::ThreadSafe> FFormModelPtr;
}