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
#include "BonusRate.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FRateModel final : public FGs2Object, public TSharedFromThis<FRateModel>
    {
        TOptional<FString> RateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> AcquireExperienceSuffixValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TSharedPtr<TArray<FString>> AcquireExperienceHierarchyValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<FBonusRate>>> BonusRatesValue;

    public:
        FRateModel();
        FRateModel(
            const FRateModel& From
        );
        virtual ~FRateModel() override = default;

        TSharedPtr<FRateModel> WithRateModelId(const TOptional<FString> RateModelId);
        TSharedPtr<FRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRateModel> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRateModel> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FRateModel> WithAcquireExperienceSuffix(const TOptional<FString> AcquireExperienceSuffix);
        TSharedPtr<FRateModel> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FRateModel> WithAcquireExperienceHierarchy(const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy);
        TSharedPtr<FRateModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FRateModel> WithBonusRates(const TSharedPtr<TArray<TSharedPtr<FBonusRate>>> BonusRates);

        TOptional<FString> GetRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetAcquireExperienceSuffix() const;
        TOptional<FString> GetMaterialInventoryModelId() const;
        TSharedPtr<TArray<FString>> GetAcquireExperienceHierarchy() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<TSharedPtr<FBonusRate>>> GetBonusRates() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FRateModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRateModel, ESPMode::ThreadSafe> FRateModelPtr;
}