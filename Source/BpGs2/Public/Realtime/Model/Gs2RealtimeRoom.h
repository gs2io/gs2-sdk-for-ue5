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
#include "Realtime/Domain/Model/Gs2RealtimeEzRoomDomain.h"
#include "Gs2RealtimeRoom.generated.h"

USTRUCT(BlueprintType)
struct FGs2RealtimeRoom
{
    GENERATED_BODY()

    Gs2::UE5::Realtime::Domain::Model::FEzRoomDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RealtimeRoomValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString IpAddress = "";
    UPROPERTY(BlueprintReadOnly)
    int32 Port = 0;
    UPROPERTY(BlueprintReadOnly)
    FString EncryptionKey = "";
};

inline FGs2RealtimeRoomValue EzRoomToFGs2RealtimeRoomValue(
    const Gs2::UE5::Realtime::Model::FEzRoomPtr Model
)
{
    FGs2RealtimeRoomValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.IpAddress = Model->GetIpAddress() ? *Model->GetIpAddress() : "";
    Value.Port = Model->GetPort() ? *Model->GetPort() : 0;
    Value.EncryptionKey = Model->GetEncryptionKey() ? *Model->GetEncryptionKey() : "";
    return Value;
}

inline Gs2::UE5::Realtime::Model::FEzRoomPtr FGs2RealtimeRoomValueToEzRoom(
    const FGs2RealtimeRoomValue Model
)
{
    return MakeShared<Gs2::UE5::Realtime::Model::FEzRoom>()
        ->WithName(Model.Name)
        ->WithIpAddress(Model.IpAddress)
        ->WithPort(Model.Port)
        ->WithEncryptionKey(Model.EncryptionKey);
}

UCLASS()
class BPGS2_API UGs2RealtimeRoomFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};