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
#include "Chat/Domain/Model/Gs2ChatEzUserGameSessionDomain.h"
#include "Chat/Domain/Model/Gs2ChatEzUserDomain.h"
#include "Gs2ChatUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatUser
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2ChatUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Room", Category="Game Server Services|GS2-Chat|Namespace|User|Room", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Room") FGs2ChatRoom Room(
        FGs2ChatUser User,
        FString RoomName,
        FString Password
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::OwnRoom", Category="Game Server Services|GS2-Chat|Namespace|User|Room", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Room") FGs2ChatOwnRoom OwnRoom(
        FGs2ChatOwnUser User,
        FString RoomName,
        FString Password
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::OwnSubscribe", Category="Game Server Services|GS2-Chat|Namespace|User|Subscribe", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Subscribe") FGs2ChatOwnSubscribe OwnSubscribe(
        FGs2ChatOwnUser User,
        FString RoomName
    );
};