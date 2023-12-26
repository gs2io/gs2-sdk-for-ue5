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
#include "Grade/Domain/Model/Gs2GradeEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2GradeNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Grade::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2GradeNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Grade::GradeModel", Category="Game Server Services|GS2-Grade|Namespace|GradeModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="GradeModel") FGs2GradeGradeModel GradeModel(
        FGs2GradeNamespace Namespace,
        FString GradeName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Grade::Me", Category="Game Server Services|GS2-Grade|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2GradeOwnUser Me(
        FGs2GradeNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};