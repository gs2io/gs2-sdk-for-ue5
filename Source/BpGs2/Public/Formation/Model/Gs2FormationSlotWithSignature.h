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

#include "Formation/Model/Gs2FormationEzSlotWithSignature.h"
#include "Gs2FormationSlotWithSignature.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationSlotWithSignature
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString PropertyType = "";
    UPROPERTY(BlueprintReadWrite)
    FString Body = "";
    UPROPERTY(BlueprintReadWrite)
    FString Signature = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
};

inline FGs2FormationSlotWithSignature EzSlotWithSignatureToFGs2FormationSlotWithSignature(
    const Gs2::UE5::Formation::Model::FEzSlotWithSignaturePtr Model
)
{
    FGs2FormationSlotWithSignature Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.PropertyType = Model->GetPropertyType() ? *Model->GetPropertyType() : "";
    Value.Body = Model->GetBody() ? *Model->GetBody() : "";
    Value.Signature = Model->GetSignature() ? *Model->GetSignature() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzSlotWithSignaturePtr FGs2FormationSlotWithSignatureToEzSlotWithSignature(
    const FGs2FormationSlotWithSignature Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzSlotWithSignature>()
        ->WithName(Model.Name)
        ->WithPropertyType(Model.PropertyType)
        ->WithBody(Model.Body)
        ->WithSignature(Model.Signature)
        ->WithMetadata(Model.Metadata);
}