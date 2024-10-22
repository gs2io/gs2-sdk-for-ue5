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
#include "Gs2Mission/Public/Mission/Model/CompleteNotification.h"
#include "Gs2Mission.generated.h"

USTRUCT(BlueprintType)
struct FGs2Mission
{
    GENERATED_BODY()

    Gs2::UE5::Mission::Domain::FEzGs2MissionPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MissionCompleteNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GroupName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TaskName = "";
};

inline FGs2MissionCompleteNotification EzCompleteNotificationToFGs2MissionCompleteNotification(
    const Gs2::Mission::Model::FCompleteNotificationPtr Model
)
{
    FGs2MissionCompleteNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.GroupName = Model->GetGroupName() ? *Model->GetGroupName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TaskName = Model->GetTaskName() ? *Model->GetTaskName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzMissionCompleteNotificationEvent, FGs2MissionCompleteNotification, Notification);

USTRUCT(BlueprintType)
struct FBpMissionCompleteNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzMissionCompleteNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2MissionFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Service", Category="Game Server Services|GS2-Mission", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Mission Service(
        FGs2Client Client,
        FBpMissionCompleteNotificationEvent CompleteNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Namespace", Category="Game Server Services|GS2-Mission|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2MissionNamespace Namespace(
        FGs2Mission Service,
        FString NamespaceName
    );

};