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
#include "Ranking/Domain/Model/Gs2RankingEzCategoryModelDomain.h"
#include "Gs2RankingCategoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingCategoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzCategoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingCategoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FString EntryPeriodEventId = "";
    UPROPERTY(BlueprintReadOnly)
    FString AccessPeriodEventId = "";
};

inline FGs2RankingCategoryModelValue EzCategoryModelToFGs2RankingCategoryModelValue(
    const Gs2::UE5::Ranking::Model::FEzCategoryModelPtr Model
)
{
    FGs2RankingCategoryModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.EntryPeriodEventId = Model->GetEntryPeriodEventId() ? *Model->GetEntryPeriodEventId() : "";
    Value.AccessPeriodEventId = Model->GetAccessPeriodEventId() ? *Model->GetAccessPeriodEventId() : "";
    return Value;
}

inline Gs2::UE5::Ranking::Model::FEzCategoryModelPtr FGs2RankingCategoryModelValueToEzCategoryModel(
    const FGs2RankingCategoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Ranking::Model::FEzCategoryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithEntryPeriodEventId(Model.EntryPeriodEventId)
        ->WithAccessPeriodEventId(Model.AccessPeriodEventId);
}

UCLASS()
class BPGS2_API UGs2RankingCategoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};