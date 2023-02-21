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

namespace Gs2::Experience::Request
{
    class FCreateExperienceModelMasterRequest;

    class GS2EXPERIENCE_API FCreateExperienceModelMasterRequest final : public TSharedFromThis<FCreateExperienceModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> DefaultExperienceValue;
        TOptional<int64> DefaultRankCapValue;
        TOptional<int64> MaxRankCapValue;
        TOptional<FString> RankThresholdNameValue;
        
    public:
        
        FCreateExperienceModelMasterRequest();
        FCreateExperienceModelMasterRequest(
            const FCreateExperienceModelMasterRequest& From
        );
        ~FCreateExperienceModelMasterRequest() = default;

        TSharedPtr<FCreateExperienceModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithDefaultExperience(const TOptional<int64> DefaultExperience);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithDefaultRankCap(const TOptional<int64> DefaultRankCap);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithMaxRankCap(const TOptional<int64> MaxRankCap);
        TSharedPtr<FCreateExperienceModelMasterRequest> WithRankThresholdName(const TOptional<FString> RankThresholdName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetDefaultExperience() const;
        FString GetDefaultExperienceString() const;
        TOptional<int64> GetDefaultRankCap() const;
        FString GetDefaultRankCapString() const;
        TOptional<int64> GetMaxRankCap() const;
        FString GetMaxRankCapString() const;
        TOptional<FString> GetRankThresholdName() const;

        static TSharedPtr<FCreateExperienceModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateExperienceModelMasterRequest, ESPMode::ThreadSafe> FCreateExperienceModelMasterRequestPtr;
}