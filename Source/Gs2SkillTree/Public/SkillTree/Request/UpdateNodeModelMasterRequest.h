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
    class FUpdateNodeModelMasterRequest;

    class GS2SKILLTREE_API FUpdateNodeModelMasterRequest final : public TSharedFromThis<FUpdateNodeModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NodeModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActionsValue;
        TOptional<float> RestrainReturnRateValue;
        TSharedPtr<TArray<FString>> PremiseNodeNamesValue;
        
    public:
        
        FUpdateNodeModelMasterRequest();
        FUpdateNodeModelMasterRequest(
            const FUpdateNodeModelMasterRequest& From
        );
        ~FUpdateNodeModelMasterRequest() = default;

        TSharedPtr<FUpdateNodeModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithNodeModelName(const TOptional<FString> NodeModelName);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);
        TSharedPtr<FUpdateNodeModelMasterRequest> WithPremiseNodeNames(
            const TSharedPtr<TArray<FString>> PremiseNodeNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetNodeModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetReleaseConsumeActions() const;
        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;
        TSharedPtr<TArray<FString>> GetPremiseNodeNames() const;

        static TSharedPtr<FUpdateNodeModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNodeModelMasterRequest, ESPMode::ThreadSafe> FUpdateNodeModelMasterRequestPtr;
}