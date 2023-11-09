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
#include "MegaField/Domain/Model/Gs2MegaFieldEzAreaModelDomain.h"
#include "MegaField/Model/Gs2MegaFieldLayerModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MegaFieldAreaModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldAreaModel
{
    GENERATED_BODY()

    Gs2::UE5::MegaField::Domain::Model::FEzAreaModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MegaFieldAreaModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2MegaFieldLayerModelValue> LayerModels = TArray<FGs2MegaFieldLayerModelValue>();
};

inline FGs2MegaFieldAreaModelValue EzAreaModelToFGs2MegaFieldAreaModelValue(
    const Gs2::UE5::MegaField::Model::FEzAreaModelPtr Model
)
{
    FGs2MegaFieldAreaModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldAreaModelFunctionLibrary::EzAreaModelToFGs2MegaFieldAreaModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.LayerModels = Model->GetLayerModels() ? [&]
    {
        TArray<FGs2MegaFieldLayerModelValue> r;
        for (auto v : *Model->GetLayerModels())
        {
            r.Add(EzLayerModelToFGs2MegaFieldLayerModelValue(v));
        }
        return r;
    }() : TArray<FGs2MegaFieldLayerModelValue>();
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzAreaModelPtr FGs2MegaFieldAreaModelValueToEzAreaModel(
    const FGs2MegaFieldAreaModelValue Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzAreaModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithLayerModels([&]{
            auto r = MakeShared<TArray<Gs2::UE5::MegaField::Model::FEzLayerModelPtr>>();
            for (auto v : Model.LayerModels) {
                r->Add(FGs2MegaFieldLayerModelValueToEzLayerModel(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2MegaFieldAreaModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::MegaField::LayerModel", Category="Game Server Services|GS2-MegaField|Namespace|AreaModel|LayerModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="LayerModel") FGs2MegaFieldLayerModel LayerModel(
        FGs2MegaFieldAreaModel AreaModel,
        FString LayerModelName
    );
};