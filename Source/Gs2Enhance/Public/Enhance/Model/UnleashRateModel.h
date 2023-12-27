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
#include "UnleashRateEntryModel.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashRateModel final : public Gs2Object, public TSharedFromThis<FUnleashRateModel>
    {
        TOptional<FString> UnleashRateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> GradeModelIdValue;
        TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GradeEntriesValue;

    public:
        FUnleashRateModel();
        FUnleashRateModel(
            const FUnleashRateModel& From
        );
        virtual ~FUnleashRateModel() override = default;

        TSharedPtr<FUnleashRateModel> WithUnleashRateModelId(const TOptional<FString> UnleashRateModelId);
        TSharedPtr<FUnleashRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FUnleashRateModel> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUnleashRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUnleashRateModel> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FUnleashRateModel> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FUnleashRateModel> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GradeEntries);

        TOptional<FString> GetUnleashRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetGradeModelId() const;
        TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GetGradeEntries() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FUnleashRateModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashRateModel, ESPMode::ThreadSafe> FUnleashRateModelPtr;
}