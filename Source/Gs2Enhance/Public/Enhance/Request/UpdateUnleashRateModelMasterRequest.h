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
#include "../Model/UnleashRateEntryModel.h"

namespace Gs2::Enhance::Request
{
    class FUpdateUnleashRateModelMasterRequest;

    class GS2ENHANCE_API FUpdateUnleashRateModelMasterRequest final : public TSharedFromThis<FUpdateUnleashRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> GradeModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FUnleashRateEntryModel>>> GradeEntriesValue;
        
    public:
        
        FUpdateUnleashRateModelMasterRequest();
        FUpdateUnleashRateModelMasterRequest(
            const FUpdateUnleashRateModelMasterRequest& From
        );
        ~FUpdateUnleashRateModelMasterRequest() = default;

        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FUpdateUnleashRateModelMasterRequest> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<Model::FUnleashRateEntryModel>>> GradeEntries);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetGradeModelId() const;TSharedPtr<TArray<TSharedPtr<Model::FUnleashRateEntryModel>>> GetGradeEntries() const;

        static TSharedPtr<FUpdateUnleashRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateUnleashRateModelMasterRequest, ESPMode::ThreadSafe> FUpdateUnleashRateModelMasterRequestPtr;
}