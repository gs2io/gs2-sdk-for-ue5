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
#include "Grade/Domain/Model/Gs2GradeEzStatusGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2GradeStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeOwnStatus
{
    GENERATED_BODY()

    Gs2::UE5::Grade::Domain::Model::FEzStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2GradeStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString GradeName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 GradeValue = 0;
};

inline FGs2GradeStatusValue EzStatusToFGs2GradeStatusValue(
    const Gs2::UE5::Grade::Model::FEzStatusPtr Model
)
{
    FGs2GradeStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeStatusFunctionLibrary::EzStatusToFGs2GradeStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.GradeName = Model->GetGradeName() ? *Model->GetGradeName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.GradeValue = Model->GetGradeValue() ? *Model->GetGradeValue() : 0;
    return Value;
}

inline Gs2::UE5::Grade::Model::FEzStatusPtr FGs2GradeStatusValueToEzStatus(
    const FGs2GradeStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Grade::Model::FEzStatus>()
        ->WithGradeName(Model.GradeName)
        ->WithPropertyId(Model.PropertyId)
        ->WithGradeValue(Model.GradeValue);
}

UCLASS()
class BPGS2_API UGs2GradeStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};