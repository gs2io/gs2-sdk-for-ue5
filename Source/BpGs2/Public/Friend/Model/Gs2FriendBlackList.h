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
#include "Friend/Domain/Model/Gs2FriendEzBlackListGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FriendBlackList.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnBlackList
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendBlackListValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FString> TargetUserIds = TArray<FString>();
};

inline FGs2FriendBlackListValue EzBlackListToFGs2FriendBlackListValue(
    const Gs2::UE5::Friend::Model::FEzBlackListPtr Model
)
{
    FGs2FriendBlackListValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendBlackListFunctionLibrary::EzBlackListToFGs2FriendBlackListValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TargetUserIds = Model->GetTargetUserIds() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetTargetUserIds())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzBlackListPtr FGs2FriendBlackListValueToEzBlackList(
    const FGs2FriendBlackListValue Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzBlackList>()
        ->WithUserId(Model.UserId)
        ->WithTargetUserIds([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.TargetUserIds) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2FriendBlackListFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};