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
#include "SerialKey/Domain/Model/Gs2SerialKeyEzCampaignModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SerialKeyCampaignModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2SerialKeyCampaignModel
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzCampaignModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SerialKeyCampaignModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    bool EnableCampaignCode = false;
};

inline FGs2SerialKeyCampaignModelValue EzCampaignModelToFGs2SerialKeyCampaignModelValue(
    const Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr Model
)
{
    FGs2SerialKeyCampaignModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyCampaignModelFunctionLibrary::EzCampaignModelToFGs2SerialKeyCampaignModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.EnableCampaignCode = Model->GetEnableCampaignCode() ? *Model->GetEnableCampaignCode() : false;
    return Value;
}

inline Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr FGs2SerialKeyCampaignModelValueToEzCampaignModel(
    const FGs2SerialKeyCampaignModelValue Model
)
{
    return MakeShared<Gs2::UE5::SerialKey::Model::FEzCampaignModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithEnableCampaignCode(Model.EnableCampaignCode);
}

UCLASS()
class BPGS2_API UGs2SerialKeyCampaignModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};