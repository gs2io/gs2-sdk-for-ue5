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
#include "../Model/TierModel.h"

namespace Gs2::SeasonRating::Request
{
    class FCreateSeasonModelMasterRequest;

    class GS2SEASONRATING_API FCreateSeasonModelMasterRequest final : public TSharedFromThis<FCreateSeasonModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> TiersValue;
        TOptional<FString> ExperienceModelIdValue;
        
    public:
        
        FCreateSeasonModelMasterRequest();
        FCreateSeasonModelMasterRequest(
            const FCreateSeasonModelMasterRequest& From
        );
        ~FCreateSeasonModelMasterRequest() = default;

        TSharedPtr<FCreateSeasonModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithTiers(const TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> Tiers);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> GetTiers() const;
        TOptional<FString> GetExperienceModelId() const;

        static TSharedPtr<FCreateSeasonModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSeasonModelMasterRequest, ESPMode::ThreadSafe> FCreateSeasonModelMasterRequestPtr;
}