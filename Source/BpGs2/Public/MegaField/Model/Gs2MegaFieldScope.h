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

#include "MegaField/Model/Gs2MegaFieldEzScope.h"
#include "Gs2MegaFieldScope.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldScope
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float R = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Limit = 0;
};

inline FGs2MegaFieldScope EzScopeToFGs2MegaFieldScope(
    const Gs2::UE5::MegaField::Model::FEzScopePtr Model
)
{
    FGs2MegaFieldScope Value;
    Value.R = Model->GetR() ? *Model->GetR() : 0;
    Value.Limit = Model->GetLimit() ? *Model->GetLimit() : 0;
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzScopePtr FGs2MegaFieldScopeToEzScope(
    const FGs2MegaFieldScope Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzScope>()
        ->WithR(Model.R)
        ->WithLimit(Model.Limit);
}