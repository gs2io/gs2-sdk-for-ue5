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
#include "../Model/AcquireActionRate.h"

namespace Gs2::Experience::Request
{
    class FUpdateExperienceModelMasterRequest;

    class GS2EXPERIENCE_API FUpdateExperienceModelMasterRequest final : public TSharedFromThis<FUpdateExperienceModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> DefaultExperienceValue;
        TOptional<int64> DefaultRankCapValue;
        TOptional<int64> MaxRankCapValue;
        TOptional<FString> RankThresholdNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRatesValue;
        
    public:
        
        FUpdateExperienceModelMasterRequest();
        FUpdateExperienceModelMasterRequest(
            const FUpdateExperienceModelMasterRequest& From
        );
        ~FUpdateExperienceModelMasterRequest() = default;

        TSharedPtr<FUpdateExperienceModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithDefaultExperience(const TOptional<int64> DefaultExperience);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithDefaultRankCap(const TOptional<int64> DefaultRankCap);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithMaxRankCap(const TOptional<int64> MaxRankCap);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithRankThresholdName(const TOptional<FString> RankThresholdName);
        TSharedPtr<FUpdateExperienceModelMasterRequest> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetDefaultExperience() const;
        FString GetDefaultExperienceString() const;
        TOptional<int64> GetDefaultRankCap() const;
        FString GetDefaultRankCapString() const;
        TOptional<int64> GetMaxRankCap() const;
        FString GetMaxRankCapString() const;
        TOptional<FString> GetRankThresholdName() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> GetAcquireActionRates() const;

        static TSharedPtr<FUpdateExperienceModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequestPtr;
}