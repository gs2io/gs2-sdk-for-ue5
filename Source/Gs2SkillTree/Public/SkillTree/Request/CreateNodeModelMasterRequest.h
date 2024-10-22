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
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::SkillTree::Request
{
    class FCreateNodeModelMasterRequest;

    class GS2SKILLTREE_API FCreateNodeModelMasterRequest final : public TSharedFromThis<FCreateNodeModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ReleaseVerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActionsValue;
        TOptional<float> RestrainReturnRateValue;
        TSharedPtr<TArray<FString>> PremiseNodeNamesValue;
        
    public:
        
        FCreateNodeModelMasterRequest();
        FCreateNodeModelMasterRequest(
            const FCreateNodeModelMasterRequest& From
        );
        ~FCreateNodeModelMasterRequest() = default;

        TSharedPtr<FCreateNodeModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNodeModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateNodeModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNodeModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNodeModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateNodeModelMasterRequest> WithReleaseVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ReleaseVerifyActions);
        TSharedPtr<FCreateNodeModelMasterRequest> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FCreateNodeModelMasterRequest> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);
        TSharedPtr<FCreateNodeModelMasterRequest> WithPremiseNodeNames(
            const TSharedPtr<TArray<FString>> PremiseNodeNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetReleaseVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetReleaseConsumeActions() const;
        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;
        TSharedPtr<TArray<FString>> GetPremiseNodeNames() const;

        static TSharedPtr<FCreateNodeModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNodeModelMasterRequest> FCreateNodeModelMasterRequestPtr;
}