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
#include "Chat/Domain/Model/Gs2ChatEzCategoryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ChatCategoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatCategoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzCategoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatCategoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Category = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RejectAccessTokenPost = "";
};

inline FGs2ChatCategoryModelValue EzCategoryModelToFGs2ChatCategoryModelValue(
    const Gs2::UE5::Chat::Model::FEzCategoryModelPtr Model
)
{
    FGs2ChatCategoryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatCategoryModelFunctionLibrary::EzCategoryModelToFGs2ChatCategoryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Category = Model->GetCategory() ? *Model->GetCategory() : 0;
    Value.RejectAccessTokenPost = Model->GetRejectAccessTokenPost() ? *Model->GetRejectAccessTokenPost() : "";
    return Value;
}

inline Gs2::UE5::Chat::Model::FEzCategoryModelPtr FGs2ChatCategoryModelValueToEzCategoryModel(
    const FGs2ChatCategoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Chat::Model::FEzCategoryModel>()
        ->WithCategory(Model.Category)
        ->WithRejectAccessTokenPost(Model.RejectAccessTokenPost);
}

UCLASS()
class BPGS2_API UGs2ChatCategoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};