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
#include "Core/Gs2Object.h"
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::SkillTree::Model
{
    class GS2SKILLTREE_API FNodeModel final : public Gs2Object, public TSharedFromThis<FNodeModel>
    {
        TOptional<FString> NodeModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ReleaseConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReturnAcquireActionsValue;
        TOptional<float> RestrainReturnRateValue;
        TSharedPtr<TArray<FString>> PremiseNodeNamesValue;

    public:
        FNodeModel();
        FNodeModel(
            const FNodeModel& From
        );
        virtual ~FNodeModel() override = default;

        TSharedPtr<FNodeModel> WithNodeModelId(const TOptional<FString> NodeModelId);
        TSharedPtr<FNodeModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FNodeModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FNodeModel> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FNodeModel> WithReturnAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> ReturnAcquireActions);
        TSharedPtr<FNodeModel> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);
        TSharedPtr<FNodeModel> WithPremiseNodeNames(const TSharedPtr<TArray<FString>> PremiseNodeNames);

        TOptional<FString> GetNodeModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetReleaseConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetReturnAcquireActions() const;
        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;
        TSharedPtr<TArray<FString>> GetPremiseNodeNames() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetNodeModelNameFromGrn(const FString Grn);

        static TSharedPtr<FNodeModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNodeModel, ESPMode::ThreadSafe> FNodeModelPtr;
}