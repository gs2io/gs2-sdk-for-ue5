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
#include "Chat/Domain/Model/Gs2ChatEzMessageGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ChatMessage.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatOwnMessage
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatMessageValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RoomName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Category = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2ChatMessageValue EzMessageToFGs2ChatMessageValue(
    const Gs2::UE5::Chat::Model::FEzMessagePtr Model
)
{
    FGs2ChatMessageValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatMessageFunctionLibrary::EzMessageToFGs2ChatMessageValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.RoomName = Model->GetRoomName() ? *Model->GetRoomName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Category = Model->GetCategory() ? *Model->GetCategory() : 0;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Chat::Model::FEzMessagePtr FGs2ChatMessageValueToEzMessage(
    const FGs2ChatMessageValue Model
)
{
    return MakeShared<Gs2::UE5::Chat::Model::FEzMessage>()
        ->WithName(Model.Name)
        ->WithRoomName(Model.RoomName)
        ->WithUserId(Model.UserId)
        ->WithCategory(Model.Category)
        ->WithMetadata(Model.Metadata)
        ->WithCreatedAt(Model.CreatedAt);
}

UCLASS()
class BPGS2_API UGs2ChatMessageFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};