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

#include "Money2/Model/Gs2Money2EzGooglePlayContent.h"
#include "Gs2Money2GooglePlayContent.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2GooglePlayContent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ProductId = "";
};

inline FGs2Money2GooglePlayContent EzGooglePlayContentToFGs2Money2GooglePlayContent(
    const Gs2::UE5::Money2::Model::FEzGooglePlayContentPtr Model
)
{
    FGs2Money2GooglePlayContent Value;
    Value.ProductId = Model->GetProductId() ? *Model->GetProductId() : "";
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzGooglePlayContentPtr FGs2Money2GooglePlayContentToEzGooglePlayContent(
    const FGs2Money2GooglePlayContent Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzGooglePlayContent>()
        ->WithProductId(Model.ProductId);
}