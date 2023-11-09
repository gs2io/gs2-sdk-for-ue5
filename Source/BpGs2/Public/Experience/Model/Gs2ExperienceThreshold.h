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

#include "Experience/Model/Gs2ExperienceEzThreshold.h"
#include "Gs2ExperienceThreshold.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceThreshold
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<int64> Values = TArray<int64>();
};

inline FGs2ExperienceThreshold EzThresholdToFGs2ExperienceThreshold(
    const Gs2::UE5::Experience::Model::FEzThresholdPtr Model
)
{
    FGs2ExperienceThreshold Value;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Values = Model->GetValues() ? [&]
    {
        TArray<int64> r;
        for (auto v : *Model->GetValues())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<int64>();
    return Value;
}

inline Gs2::UE5::Experience::Model::FEzThresholdPtr FGs2ExperienceThresholdToEzThreshold(
    const FGs2ExperienceThreshold Model
)
{
    return MakeShared<Gs2::UE5::Experience::Model::FEzThreshold>()
        ->WithMetadata(Model.Metadata)
        ->WithValues([&]{
            auto r = MakeShared<TArray<int64>>();
            for (auto v : Model.Values) {
                r->Add(v);
            }
            return r;
        }());
}