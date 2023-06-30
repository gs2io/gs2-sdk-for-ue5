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
#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectHistoryGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DatastoreDataObjectHistory.generated.h"

USTRUCT(BlueprintType)
struct FGs2DatastoreOwnDataObjectHistory
{
    GENERATED_BODY()

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DatastoreDataObjectHistoryValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString DataObjectHistoryId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Generation = "";
    UPROPERTY(BlueprintReadOnly)
    int64 ContentLength = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2DatastoreDataObjectHistoryValue EzDataObjectHistoryToFGs2DatastoreDataObjectHistoryValue(
    const Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr Model
)
{
    FGs2DatastoreDataObjectHistoryValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDataObjectHistoryFunctionLibrary::EzDataObjectHistoryToFGs2DatastoreDataObjectHistoryValue] Model parameter specification is missing."))
        return Value;
    }
    Value.DataObjectHistoryId = Model->GetDataObjectHistoryId() ? *Model->GetDataObjectHistoryId() : "";
    Value.Generation = Model->GetGeneration() ? *Model->GetGeneration() : "";
    Value.ContentLength = Model->GetContentLength() ? *Model->GetContentLength() : 0;
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr FGs2DatastoreDataObjectHistoryValueToEzDataObjectHistory(
    const FGs2DatastoreDataObjectHistoryValue Model
)
{
    return MakeShared<Gs2::UE5::Datastore::Model::FEzDataObjectHistory>()
        ->WithDataObjectHistoryId(Model.DataObjectHistoryId)
        ->WithGeneration(Model.Generation)
        ->WithContentLength(Model.ContentLength)
        ->WithCreatedAt(Model.CreatedAt);
}

UCLASS()
class BPGS2_API UGs2DatastoreDataObjectHistoryFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};