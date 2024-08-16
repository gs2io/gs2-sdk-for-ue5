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
#include "Dom/JsonObject.h"
#include "../Model/BonusRate.h"

namespace Gs2::Enhance::Request
{
    class FCreateRateModelMasterRequest;

    class GS2ENHANCE_API FCreateRateModelMasterRequest final : public TSharedFromThis<FCreateRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> AcquireExperienceSuffixValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TSharedPtr<TArray<FString>> AcquireExperienceHierarchyValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRatesValue;
        
    public:
        
        FCreateRateModelMasterRequest();
        FCreateRateModelMasterRequest(
            const FCreateRateModelMasterRequest& From
        );
        ~FCreateRateModelMasterRequest() = default;

        TSharedPtr<FCreateRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRateModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRateModelMasterRequest> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FCreateRateModelMasterRequest> WithAcquireExperienceSuffix(const TOptional<FString> AcquireExperienceSuffix);
        TSharedPtr<FCreateRateModelMasterRequest> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FCreateRateModelMasterRequest> WithAcquireExperienceHierarchy(
            const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy);
        TSharedPtr<FCreateRateModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FCreateRateModelMasterRequest> WithBonusRates(const TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRates);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetAcquireExperienceSuffix() const;
        TOptional<FString> GetMaterialInventoryModelId() const;
        TSharedPtr<TArray<FString>> GetAcquireExperienceHierarchy() const;
        TOptional<FString> GetExperienceModelId() const;TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> GetBonusRates() const;

        static TSharedPtr<FCreateRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRateModelMasterRequest> FCreateRateModelMasterRequestPtr;
}