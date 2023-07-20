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
#include "../Model/RarityParameterCountModel.h"
#include "../Model/RarityParameterValueModel.h"

namespace Gs2::Enchant::Request
{
    class FCreateRarityParameterModelMasterRequest;

    class GS2ENCHANT_API FCreateRarityParameterModelMasterRequest final : public TSharedFromThis<FCreateRarityParameterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParameterCountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCountsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> ParametersValue;
        
    public:
        
        FCreateRarityParameterModelMasterRequest();
        FCreateRarityParameterModelMasterRequest(
            const FCreateRarityParameterModelMasterRequest& From
        );
        ~FCreateRarityParameterModelMasterRequest() = default;

        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithMaximumParameterCount(const TOptional<int32> MaximumParameterCount);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithParameterCounts(const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCounts);
        TSharedPtr<FCreateRarityParameterModelMasterRequest> WithParameters(const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> Parameters);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParameterCount() const;
        FString GetMaximumParameterCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> GetParameterCounts() const;TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> GetParameters() const;

        static TSharedPtr<FCreateRarityParameterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRarityParameterModelMasterRequest, ESPMode::ThreadSafe> FCreateRarityParameterModelMasterRequestPtr;
}