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
#include "Inbox/Domain/Model/Gs2InboxEzUserGameSessionDomain.h"
#include "Gs2InboxUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2InboxOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Inbox::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2InboxUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::OwnMessage", Category="Game Server Services|GS2-Inbox|Namespace|User|Message", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Message") FGs2InboxOwnMessage OwnMessage(
        FGs2InboxOwnUser User,
        FString MessageName
    );
};