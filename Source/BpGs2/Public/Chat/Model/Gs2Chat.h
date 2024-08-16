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

#include "Core/Model/Gs2Client.h"
#include "Gs2Chat/Public/Chat/Model/PostNotification.h"
#include "Gs2Chat.generated.h"

USTRUCT(BlueprintType)
struct FGs2Chat
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::FEzGs2ChatPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatPostNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString RoomName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Category = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 CreatedAt = 0;
};

inline FGs2ChatPostNotification EzPostNotificationToFGs2ChatPostNotification(
    const Gs2::Chat::Model::FPostNotificationPtr Model
)
{
    FGs2ChatPostNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.RoomName = Model->GetRoomName() ? *Model->GetRoomName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Category = Model->GetCategory() ? *Model->GetCategory() : 0;
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzChatPostNotificationEvent, FGs2ChatPostNotification, Notification);

USTRUCT(BlueprintType)
struct FBpChatPostNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzChatPostNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2ChatFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Service", Category="Game Server Services|GS2-Chat", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Chat Service(
        FGs2Client Client,
        FBpChatPostNotificationEvent PostNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Namespace", Category="Game Server Services|GS2-Chat|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2ChatNamespace Namespace(
        FGs2Chat Service,
        FString NamespaceName
    );

};