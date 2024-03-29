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
#include "SerialKey/Domain/Model/Gs2SerialKeyEzSerialKeyGameSessionDomain.h"
#include "SerialKey/Domain/Model/Gs2SerialKeyEzSerialKeyDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SerialKeySerialKey.generated.h"

USTRUCT(BlueprintType)
struct FGs2SerialKeySerialKey
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SerialKeyOwnSerialKey
{
    GENERATED_BODY()

    Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SerialKeySerialKeyValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString CampaignModelName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Code = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Status = "";
};

inline FGs2SerialKeySerialKeyValue EzSerialKeyToFGs2SerialKeySerialKeyValue(
    const Gs2::UE5::SerialKey::Model::FEzSerialKeyPtr Model
)
{
    FGs2SerialKeySerialKeyValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeySerialKeyFunctionLibrary::EzSerialKeyToFGs2SerialKeySerialKeyValue] Model parameter specification is missing."))
        return Value;
    }
    Value.CampaignModelName = Model->GetCampaignModelName() ? *Model->GetCampaignModelName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Code = Model->GetCode() ? *Model->GetCode() : "";
    Value.Status = Model->GetStatus() ? *Model->GetStatus() : "";
    return Value;
}

inline Gs2::UE5::SerialKey::Model::FEzSerialKeyPtr FGs2SerialKeySerialKeyValueToEzSerialKey(
    const FGs2SerialKeySerialKeyValue Model
)
{
    return MakeShared<Gs2::UE5::SerialKey::Model::FEzSerialKey>()
        ->WithCampaignModelName(Model.CampaignModelName)
        ->WithMetadata(Model.Metadata)
        ->WithCode(Model.Code)
        ->WithStatus(Model.Status);
}

UCLASS()
class BPGS2_API UGs2SerialKeySerialKeyFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};