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
#include "BalanceParameterValueModel.h"

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FBalanceParameterModelMaster final : public Gs2Object, public TSharedFromThis<FBalanceParameterModelMaster>
    {
        TOptional<FString> BalanceParameterModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> TotalValueValue;
        TOptional<FString> InitialValueStrategyValue;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> ParametersValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FBalanceParameterModelMaster();
        FBalanceParameterModelMaster(
            const FBalanceParameterModelMaster& From
        );
        virtual ~FBalanceParameterModelMaster() override = default;

        TSharedPtr<FBalanceParameterModelMaster> WithBalanceParameterModelId(const TOptional<FString> BalanceParameterModelId);
        TSharedPtr<FBalanceParameterModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FBalanceParameterModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FBalanceParameterModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBalanceParameterModelMaster> WithTotalValue(const TOptional<int64> TotalValue);
        TSharedPtr<FBalanceParameterModelMaster> WithInitialValueStrategy(const TOptional<FString> InitialValueStrategy);
        TSharedPtr<FBalanceParameterModelMaster> WithParameters(const TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> Parameters);
        TSharedPtr<FBalanceParameterModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBalanceParameterModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBalanceParameterModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetBalanceParameterModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetTotalValue() const;
        FString GetTotalValueString() const;
        TOptional<FString> GetInitialValueStrategy() const;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> GetParameters() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);

        static TSharedPtr<FBalanceParameterModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBalanceParameterModelMaster, ESPMode::ThreadSafe> FBalanceParameterModelMasterPtr;
}