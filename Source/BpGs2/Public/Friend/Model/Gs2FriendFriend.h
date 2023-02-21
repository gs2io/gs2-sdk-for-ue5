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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Friend/Domain/Model/Gs2FriendEzFriendGameSessionDomain.h"
#include "Gs2FriendFriend.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnFriend
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzFriendGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2FriendFriendFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnFriendUser", Category="Game Server Services|GS2-Friend|Namespace|User|Friend|FriendUser", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="FriendUser") FGs2FriendOwnFriendUser OwnFriendUser(
        FGs2FriendOwnFriend Friend,
        FString TargetUserId
    );
};