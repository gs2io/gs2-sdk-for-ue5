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
#include "Dictionary/Domain/Model/Gs2DictionaryEzEntryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DictionaryEntryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2DictionaryEntryModel
{
    GENERATED_BODY()

    Gs2::UE5::Dictionary::Domain::Model::FEzEntryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DictionaryEntryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2DictionaryEntryModelValue EzEntryModelToFGs2DictionaryEntryModelValue(
    const Gs2::UE5::Dictionary::Model::FEzEntryModelPtr Model
)
{
    FGs2DictionaryEntryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryEntryModelFunctionLibrary::EzEntryModelToFGs2DictionaryEntryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Dictionary::Model::FEzEntryModelPtr FGs2DictionaryEntryModelValueToEzEntryModel(
    const FGs2DictionaryEntryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Dictionary::Model::FEzEntryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2DictionaryEntryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};