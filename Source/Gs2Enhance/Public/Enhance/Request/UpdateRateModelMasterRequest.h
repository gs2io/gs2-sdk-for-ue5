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
#include "../Model/BonusRate.h"

namespace Gs2::Enhance::Request
{
    class FUpdateRateModelMasterRequest;

    class GS2ENHANCE_API FUpdateRateModelMasterRequest final : public TSharedFromThis<FUpdateRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> AcquireExperienceSuffixValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TSharedPtr<TArray<FString>> AcquireExperienceHierarchyValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRatesValue;
        
    public:
        
        FUpdateRateModelMasterRequest();
        FUpdateRateModelMasterRequest(
            const FUpdateRateModelMasterRequest& From
        );
        ~FUpdateRateModelMasterRequest() = default;

        TSharedPtr<FUpdateRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRateModelMasterRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FUpdateRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRateModelMasterRequest> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FUpdateRateModelMasterRequest> WithAcquireExperienceSuffix(const TOptional<FString> AcquireExperienceSuffix);
        TSharedPtr<FUpdateRateModelMasterRequest> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FUpdateRateModelMasterRequest> WithAcquireExperienceHierarchy(
            const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy);
        TSharedPtr<FUpdateRateModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FUpdateRateModelMasterRequest> WithBonusRates(const TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRates);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetAcquireExperienceSuffix() const;
        TOptional<FString> GetMaterialInventoryModelId() const;
        TSharedPtr<TArray<FString>> GetAcquireExperienceHierarchy() const;
        TOptional<FString> GetExperienceModelId() const;TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> GetBonusRates() const;

        static TSharedPtr<FUpdateRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRateModelMasterRequest, ESPMode::ThreadSafe> FUpdateRateModelMasterRequestPtr;
}