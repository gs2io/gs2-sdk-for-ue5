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
#include "Mission/Domain/Model/Gs2MissionEzCounterModelDomain.h"
#include "Mission/Model/Gs2MissionCounterScopeModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MissionCounterModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionCounterModel
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::Model::FEzCounterModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionCounterModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2MissionCounterScopeModel> Scopes = TArray<FGs2MissionCounterScopeModel>();
    UPROPERTY(BlueprintReadOnly)
    FString ChallengePeriodEventId = "";
};

inline FGs2MissionCounterModelValue EzCounterModelToFGs2MissionCounterModelValue(
    const Gs2::UE5::Mission::Model::FEzCounterModelPtr Model
)
{
    FGs2MissionCounterModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionCounterModelFunctionLibrary::EzCounterModelToFGs2MissionCounterModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Scopes = Model->GetScopes() ? [&]
    {
        TArray<FGs2MissionCounterScopeModel> r;
        for (auto v : *Model->GetScopes())
        {
            r.Add(EzCounterScopeModelToFGs2MissionCounterScopeModel(v));
        }
        return r;
    }() : TArray<FGs2MissionCounterScopeModel>();
    Value.ChallengePeriodEventId = Model->GetChallengePeriodEventId() ? *Model->GetChallengePeriodEventId() : "";
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzCounterModelPtr FGs2MissionCounterModelValueToEzCounterModel(
    const FGs2MissionCounterModelValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzCounterModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithScopes([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzCounterScopeModelPtr>>();
            for (auto v : Model.Scopes) {
                r->Add(FGs2MissionCounterScopeModelToEzCounterScopeModel(v));
            }
            return r;
        }())
        ->WithChallengePeriodEventId(Model.ChallengePeriodEventId);
}

UCLASS()
class BPGS2_API UGs2MissionCounterModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};