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
#include "Dictionary/Domain/Model/Gs2DictionaryEzLikeGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DictionaryLike.generated.h"

USTRUCT(BlueprintType)
struct FGs2DictionaryOwnLike
{
    GENERATED_BODY()

    Gs2::UE5::Dictionary::Domain::Model::FEzLikeGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DictionaryLikeValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString LikeId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
};

inline FGs2DictionaryLikeValue EzLikeToFGs2DictionaryLikeValue(
    const Gs2::UE5::Dictionary::Model::FEzLikePtr Model
)
{
    FGs2DictionaryLikeValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryLikeFunctionLibrary::EzLikeToFGs2DictionaryLikeValue] Model parameter specification is missing."))
        return Value;
    }
    Value.LikeId = Model->GetLikeId() ? *Model->GetLikeId() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    return Value;
}

inline Gs2::UE5::Dictionary::Model::FEzLikePtr FGs2DictionaryLikeValueToEzLike(
    const FGs2DictionaryLikeValue Model
)
{
    return MakeShared<Gs2::UE5::Dictionary::Model::FEzLike>()
        ->WithLikeId(Model.LikeId)
        ->WithUserId(Model.UserId)
        ->WithName(Model.Name);
}

UCLASS()
class BPGS2_API UGs2DictionaryLikeFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};