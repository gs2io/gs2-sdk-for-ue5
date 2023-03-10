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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Showcase/Domain/Model/Gs2ShowcaseEzShowcaseGameSessionDomain.h"
#include "Showcase/Model/Gs2ShowcaseDisplayItem.h"
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
    TArray<FGs2ShowcaseDisplayItem> DisplayItems = TArray<FGs2ShowcaseDisplayItem>();
};

inline FGs2ShowcaseShowcaseValue EzShowcaseToFGs2ShowcaseShowcaseValue(
    const Gs2::UE5::Showcase::Model::FEzShowcasePtr Model
)
{
    FGs2ShowcaseShowcaseValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.DisplayItems = Model->GetDisplayItems() ? [&]
    {
        TArray<FGs2ShowcaseDisplayItem> r;
        for (auto v : *Model->GetDisplayItems())
        {
            r.Add(EzDisplayItemToFGs2ShowcaseDisplayItem(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseDisplayItem>();
    return Value;
}

UCLASS()
class BPGS2_API UGs2ShowcaseShowcaseFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};