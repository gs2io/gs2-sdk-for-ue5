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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzGatheringGameSessionDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzGatheringDomain.h"
#include "Matchmaking/Model/Gs2MatchmakingAttributeRange.h"
#include "Matchmaking/Model/Gs2MatchmakingCapacityOfRole.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingGathering.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnGathering
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingGathering
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingGatheringValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString GatheringId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2MatchmakingAttributeRange> AttributeRanges = TArray<FGs2MatchmakingAttributeRange>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2MatchmakingCapacityOfRole> CapacityOfRoles = TArray<FGs2MatchmakingCapacityOfRole>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FString> AllowUserIds = TArray<FString>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExpiresAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 CreatedAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2MatchmakingGatheringValue EzGatheringToFGs2MatchmakingGatheringValue(
    const Gs2::UE5::Matchmaking::Model::FEzGatheringPtr Model
)
{
    FGs2MatchmakingGatheringValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingGatheringFunctionLibrary::EzGatheringToFGs2MatchmakingGatheringValue] Model parameter specification is missing."))
        return Value;
    }
    Value.GatheringId = Model->GetGatheringId() ? *Model->GetGatheringId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.AttributeRanges = Model->GetAttributeRanges() ? [&]
    {
        TArray<FGs2MatchmakingAttributeRange> r;
        for (auto v : *Model->GetAttributeRanges())
        {
            r.Add(EzAttributeRangeToFGs2MatchmakingAttributeRange(v));
        }
        return r;
    }() : TArray<FGs2MatchmakingAttributeRange>();
    Value.CapacityOfRoles = Model->GetCapacityOfRoles() ? [&]
    {
        TArray<FGs2MatchmakingCapacityOfRole> r;
        for (auto v : *Model->GetCapacityOfRoles())
        {
            r.Add(EzCapacityOfRoleToFGs2MatchmakingCapacityOfRole(v));
        }
        return r;
    }() : TArray<FGs2MatchmakingCapacityOfRole>();
    Value.AllowUserIds = Model->GetAllowUserIds() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetAllowUserIds())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzGatheringPtr FGs2MatchmakingGatheringValueToEzGathering(
    const FGs2MatchmakingGatheringValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzGathering>()
        ->WithGatheringId(Model.GatheringId)
        ->WithName(Model.Name)
        ->WithAttributeRanges([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Matchmaking::Model::FEzAttributeRangePtr>>();
            for (auto v : Model.AttributeRanges) {
                r->Add(FGs2MatchmakingAttributeRangeToEzAttributeRange(v));
            }
            return r;
        }())
        ->WithCapacityOfRoles([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRolePtr>>();
            for (auto v : Model.CapacityOfRoles) {
                r->Add(FGs2MatchmakingCapacityOfRoleToEzCapacityOfRole(v));
            }
            return r;
        }())
        ->WithAllowUserIds([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.AllowUserIds) {
                r->Add(v);
            }
            return r;
        }())
        ->WithMetadata(Model.Metadata)
        ->WithExpiresAt(Model.ExpiresAt)
        ->WithCreatedAt(Model.CreatedAt)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2MatchmakingGatheringFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};