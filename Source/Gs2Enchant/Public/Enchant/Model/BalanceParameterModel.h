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
    class GS2ENCHANT_API FBalanceParameterModel final : public FGs2Object, public TSharedFromThis<FBalanceParameterModel>
    {
        TOptional<FString> BalanceParameterModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> TotalValueValue;
        TOptional<FString> InitialValueStrategyValue;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> ParametersValue;

    public:
        FBalanceParameterModel();
        FBalanceParameterModel(
            const FBalanceParameterModel& From
        );
        virtual ~FBalanceParameterModel() override = default;

        TSharedPtr<FBalanceParameterModel> WithBalanceParameterModelId(const TOptional<FString> BalanceParameterModelId);
        TSharedPtr<FBalanceParameterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FBalanceParameterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBalanceParameterModel> WithTotalValue(const TOptional<int64> TotalValue);
        TSharedPtr<FBalanceParameterModel> WithInitialValueStrategy(const TOptional<FString> InitialValueStrategy);
        TSharedPtr<FBalanceParameterModel> WithParameters(const TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> Parameters);

        TOptional<FString> GetBalanceParameterModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetTotalValue() const;
        FString GetTotalValueString() const;
        TOptional<FString> GetInitialValueStrategy() const;
        TSharedPtr<TArray<TSharedPtr<FBalanceParameterValueModel>>> GetParameters() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);

        static TSharedPtr<FBalanceParameterModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBalanceParameterModel, ESPMode::ThreadSafe> FBalanceParameterModelPtr;
}