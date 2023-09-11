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

namespace Gs2::SkillTree::Model
{
    class GS2SKILLTREE_API FNodeModelMaster final : public Gs2Object, public TSharedFromThis<FNodeModelMaster>
    {
        TOptional<FString> NodeModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ReleaseConsumeActionsValue;
        TOptional<float> RestrainReturnRateValue;
        TSharedPtr<TArray<FString>> PremiseNodeNamesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FNodeModelMaster();
        FNodeModelMaster(
            const FNodeModelMaster& From
        );
        virtual ~FNodeModelMaster() override = default;

        TSharedPtr<FNodeModelMaster> WithNodeModelId(const TOptional<FString> NodeModelId);
        TSharedPtr<FNodeModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FNodeModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNodeModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FNodeModelMaster> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FNodeModelMaster> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);
        TSharedPtr<FNodeModelMaster> WithPremiseNodeNames(const TSharedPtr<TArray<FString>> PremiseNodeNames);
        TSharedPtr<FNodeModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNodeModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNodeModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNodeModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetReleaseConsumeActions() const;
        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;
        TSharedPtr<TArray<FString>> GetPremiseNodeNames() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetNodeModelNameFromGrn(const FString Grn);

        static TSharedPtr<FNodeModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNodeModelMaster, ESPMode::ThreadSafe> FNodeModelMasterPtr;
}