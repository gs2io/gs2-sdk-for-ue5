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
#include "../Model/ConsumeAction.h"

namespace Gs2::SkillTree::Request
{
    class FCreateStatusModelMasterRequest;

    class GS2SKILLTREE_API FCreateStatusModelMasterRequest final : public TSharedFromThis<FCreateStatusModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActionsValue;
        TOptional<float> RestrainReturnRateValue;
        TSharedPtr<TArray<FString>> PremiseNodeNamesValue;
        
    public:
        
        FCreateStatusModelMasterRequest();
        FCreateStatusModelMasterRequest(
            const FCreateStatusModelMasterRequest& From
        );
        ~FCreateStatusModelMasterRequest() = default;

        TSharedPtr<FCreateStatusModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStatusModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateStatusModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStatusModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStatusModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateStatusModelMasterRequest> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FCreateStatusModelMasterRequest> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);
        TSharedPtr<FCreateStatusModelMasterRequest> WithPremiseNodeNames(
            const TSharedPtr<TArray<FString>> PremiseNodeNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetReleaseConsumeActions() const;
        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;
        TSharedPtr<TArray<FString>> GetPremiseNodeNames() const;

        static TSharedPtr<FCreateStatusModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStatusModelMasterRequest, ESPMode::ThreadSafe> FCreateStatusModelMasterRequestPtr;
}