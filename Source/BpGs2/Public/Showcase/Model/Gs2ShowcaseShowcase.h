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
#include "Showcase/Domain/Model/Gs2ShowcaseEzShowcaseGameSessionDomain.h"
#include "Showcase/Model/Gs2ShowcaseDisplayItem.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ShowcaseShowcase.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseOwnShowcase
{
    GENERATED_BODY()

    Gs2::UE5::Showcase::Domain::Model::FEzShowcaseGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ShowcaseShowcaseValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2ShowcaseDisplayItemValue> DisplayItems = TArray<FGs2ShowcaseDisplayItemValue>();
};

inline FGs2ShowcaseShowcaseValue EzShowcaseToFGs2ShowcaseShowcaseValue(
    const Gs2::UE5::Showcase::Model::FEzShowcasePtr Model
)
{
    FGs2ShowcaseShowcaseValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseShowcaseFunctionLibrary::EzShowcaseToFGs2ShowcaseShowcaseValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.DisplayItems = Model->GetDisplayItems() ? [&]
    {
        TArray<FGs2ShowcaseDisplayItemValue> r;
        for (auto v : *Model->GetDisplayItems())
        {
            r.Add(EzDisplayItemToFGs2ShowcaseDisplayItemValue(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseDisplayItemValue>();
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzShowcasePtr FGs2ShowcaseShowcaseValueToEzShowcase(
    const FGs2ShowcaseShowcaseValue Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzShowcase>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithDisplayItems([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzDisplayItemPtr>>();
            for (auto v : Model.DisplayItems) {
                r->Add(FGs2ShowcaseDisplayItemValueToEzDisplayItem(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2ShowcaseShowcaseFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::OwnDisplayItem", Category="Game Server Services|GS2-Showcase|Namespace|User|Showcase|DisplayItem", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="DisplayItem") FGs2ShowcaseOwnDisplayItem OwnDisplayItem(
        FGs2ShowcaseOwnShowcase Showcase,
        FString DisplayItemId
    );
};