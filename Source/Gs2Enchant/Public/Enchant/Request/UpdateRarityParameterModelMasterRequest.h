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
    class FUpdateRarityParameterModelMasterRequest;

    class GS2ENCHANT_API FUpdateRarityParameterModelMasterRequest final : public TSharedFromThis<FUpdateRarityParameterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParameterCountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCountsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> ParametersValue;
        
    public:
        
        FUpdateRarityParameterModelMasterRequest();
        FUpdateRarityParameterModelMasterRequest(
            const FUpdateRarityParameterModelMasterRequest& From
        );
        ~FUpdateRarityParameterModelMasterRequest() = default;

        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithMaximumParameterCount(const TOptional<int32> MaximumParameterCount);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithParameterCounts(const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCounts);
        TSharedPtr<FUpdateRarityParameterModelMasterRequest> WithParameters(const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> Parameters);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParameterCount() const;
        FString GetMaximumParameterCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> GetParameterCounts() const;TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> GetParameters() const;

        static TSharedPtr<FUpdateRarityParameterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRarityParameterModelMasterRequest, ESPMode::ThreadSafe> FUpdateRarityParameterModelMasterRequestPtr;
}