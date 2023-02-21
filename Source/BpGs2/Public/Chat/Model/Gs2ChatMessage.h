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

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString RoomName = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    int32 Category = 0;
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2ChatMessageValue EzMessageToFGs2ChatMessageValue(
    const Gs2::UE5::Chat::Model::FEzMessagePtr Model
)
{
    FGs2ChatMessageValue Value;
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