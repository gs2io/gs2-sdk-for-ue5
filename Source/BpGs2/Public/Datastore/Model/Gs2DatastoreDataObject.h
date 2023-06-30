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
#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectGameSessionDomain.h"
#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DatastoreDataObject.generated.h"

USTRUCT(BlueprintType)
struct FGs2DatastoreOwnDataObject
{
    GENERATED_BODY()

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DatastoreDataObject
{
    GENERATED_BODY()

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DatastoreDataObjectValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString DataObjectId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Scope = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> AllowUserIds = TArray<FString>();
    UPROPERTY(BlueprintReadOnly)
    FString Status = "";
    UPROPERTY(BlueprintReadOnly)
    FString Generation = "";
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2DatastoreDataObjectValue EzDataObjectToFGs2DatastoreDataObjectValue(
    const Gs2::UE5::Datastore::Model::FEzDataObjectPtr Model
)
{
    FGs2DatastoreDataObjectValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDataObjectFunctionLibrary::EzDataObjectToFGs2DatastoreDataObjectValue] Model parameter specification is missing."))
        return Value;
    }
    Value.DataObjectId = Model->GetDataObjectId() ? *Model->GetDataObjectId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Scope = Model->GetScope() ? *Model->GetScope() : "";
    Value.AllowUserIds = Model->GetAllowUserIds() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetAllowUserIds())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    Value.Status = Model->GetStatus() ? *Model->GetStatus() : "";
    Value.Generation = Model->GetGeneration() ? *Model->GetGeneration() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Datastore::Model::FEzDataObjectPtr FGs2DatastoreDataObjectValueToEzDataObject(
    const FGs2DatastoreDataObjectValue Model
)
{
    return MakeShared<Gs2::UE5::Datastore::Model::FEzDataObject>()
        ->WithDataObjectId(Model.DataObjectId)
        ->WithName(Model.Name)
        ->WithUserId(Model.UserId)
        ->WithScope(Model.Scope)
        ->WithAllowUserIds([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.AllowUserIds) {
                r->Add(v);
            }
            return r;
        }())
        ->WithStatus(Model.Status)
        ->WithGeneration(Model.Generation)
        ->WithCreatedAt(Model.CreatedAt)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2DatastoreDataObjectFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::OwnDataObjectHistory", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject|DataObjectHistory", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="DataObjectHistory") FGs2DatastoreOwnDataObjectHistory OwnDataObjectHistory(
        FGs2DatastoreOwnDataObject DataObject,
        FString Generation
    );
};