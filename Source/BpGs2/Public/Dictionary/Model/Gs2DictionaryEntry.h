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
#include "Dictionary/Domain/Model/Gs2DictionaryEzEntryGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DictionaryEntry.generated.h"

USTRUCT(BlueprintType)
struct FGs2DictionaryOwnEntry
{
    GENERATED_BODY()

    Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DictionaryEntryValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString EntryId = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    int64 AcquiredAt = 0;
};

inline FGs2DictionaryEntryValue EzEntryToFGs2DictionaryEntryValue(
    const Gs2::UE5::Dictionary::Model::FEzEntryPtr Model
)
{
    FGs2DictionaryEntryValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryEntryFunctionLibrary::EzEntryToFGs2DictionaryEntryValue] Model parameter specification is missing."))
        return Value;
    }
    Value.EntryId = Model->GetEntryId() ? *Model->GetEntryId() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.AcquiredAt = Model->GetAcquiredAt() ? *Model->GetAcquiredAt() : 0;
    return Value;
}

inline Gs2::UE5::Dictionary::Model::FEzEntryPtr FGs2DictionaryEntryValueToEzEntry(
    const FGs2DictionaryEntryValue Model
)
{
    return MakeShared<Gs2::UE5::Dictionary::Model::FEzEntry>()
        ->WithEntryId(Model.EntryId)
        ->WithUserId(Model.UserId)
        ->WithName(Model.Name)
        ->WithAcquiredAt(Model.AcquiredAt);
}

UCLASS()
class BPGS2_API UGs2DictionaryEntryFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};