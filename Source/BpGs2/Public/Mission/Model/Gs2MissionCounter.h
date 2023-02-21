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
#include "Mission/Domain/Model/Gs2MissionEzCounterGameSessionDomain.h"
#include "Mission/Model/Gs2MissionScopedValue.h"
#include "Gs2MissionCounter.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionOwnCounter
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzCounterGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionCounterValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2MissionScopedValue> Values = TArray<FGs2MissionScopedValue>();
};

inline FGs2MissionCounterValue EzCounterToFGs2MissionCounterValue(
    const Gs2::UE5::Mission::Model::FEzCounterPtr Model
)
{
    FGs2MissionCounterValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Values = Model->GetValues() ? [&]
    {
        TArray<FGs2MissionScopedValue> r;
        for (auto v : *Model->GetValues())
        {
            r.Add(EzScopedValueToFGs2MissionScopedValue(v));
        }
        return r;
    }() : TArray<FGs2MissionScopedValue>();
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzCounterPtr FGs2MissionCounterValueToEzCounter(
    const FGs2MissionCounterValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzCounter>()
        ->WithName(Model.Name)
        ->WithValues([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzScopedValuePtr>>();
            for (auto v : Model.Values) {
                r->Add(FGs2MissionScopedValueToEzScopedValue(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2MissionCounterFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};