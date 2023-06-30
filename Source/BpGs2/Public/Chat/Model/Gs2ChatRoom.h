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
#include "Chat/Domain/Model/Gs2ChatEzRoomGameSessionDomain.h"
#include "Chat/Domain/Model/Gs2ChatEzRoomDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ChatRoom.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatOwnRoom
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatRoom
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzRoomDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatRoomValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2ChatRoomValue EzRoomToFGs2ChatRoomValue(
    const Gs2::UE5::Chat::Model::FEzRoomPtr Model
)
{
    FGs2ChatRoomValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatRoomFunctionLibrary::EzRoomToFGs2ChatRoomValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Chat::Model::FEzRoomPtr FGs2ChatRoomValueToEzRoom(
    const FGs2ChatRoomValue Model
)
{
    return MakeShared<Gs2::UE5::Chat::Model::FEzRoom>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2ChatRoomFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::OwnMessage", Category="Game Server Services|GS2-Chat|Namespace|User|Room|Message", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Message") FGs2ChatOwnMessage OwnMessage(
        FGs2ChatOwnRoom Room,
        FString MessageName
    );
};