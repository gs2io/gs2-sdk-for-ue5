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
#include "../Model/TierModel.h"

namespace Gs2::SeasonRating::Request
{
    class FUpdateSeasonModelMasterRequest;

    class GS2SEASONRATING_API FUpdateSeasonModelMasterRequest final : public TSharedFromThis<FUpdateSeasonModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> TiersValue;
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FUpdateSeasonModelMasterRequest();
        FUpdateSeasonModelMasterRequest(
            const FUpdateSeasonModelMasterRequest& From
        );
        ~FUpdateSeasonModelMasterRequest() = default;

        TSharedPtr<FUpdateSeasonModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithTiers(const TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> Tiers);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FUpdateSeasonModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> GetTiers() const;
        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FUpdateSeasonModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequestPtr;
}