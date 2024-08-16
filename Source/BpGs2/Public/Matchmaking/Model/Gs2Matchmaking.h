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
#include "Gs2Matchmaking/Public/Matchmaking/Model/JoinNotification.h"
#include "Gs2Matchmaking/Public/Matchmaking/Model/LeaveNotification.h"
#include "Gs2Matchmaking/Public/Matchmaking/Model/CompleteNotification.h"
#include "Gs2Matchmaking/Public/Matchmaking/Model/ChangeRatingNotification.h"
#include "Gs2Matchmaking.generated.h"

USTRUCT(BlueprintType)
struct FGs2Matchmaking
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::FEzGs2MatchmakingPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingJoinNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GatheringName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString JoinUserId = "";
};

inline FGs2MatchmakingJoinNotification EzJoinNotificationToFGs2MatchmakingJoinNotification(
    const Gs2::Matchmaking::Model::FJoinNotificationPtr Model
)
{
    FGs2MatchmakingJoinNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.GatheringName = Model->GetGatheringName() ? *Model->GetGatheringName() : "";
    Value.JoinUserId = Model->GetJoinUserId() ? *Model->GetJoinUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzMatchmakingJoinNotificationEvent, FGs2MatchmakingJoinNotification, Notification);

USTRUCT(BlueprintType)
struct FBpMatchmakingJoinNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzMatchmakingJoinNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingLeaveNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GatheringName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString LeaveUserId = "";
};

inline FGs2MatchmakingLeaveNotification EzLeaveNotificationToFGs2MatchmakingLeaveNotification(
    const Gs2::Matchmaking::Model::FLeaveNotificationPtr Model
)
{
    FGs2MatchmakingLeaveNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.GatheringName = Model->GetGatheringName() ? *Model->GetGatheringName() : "";
    Value.LeaveUserId = Model->GetLeaveUserId() ? *Model->GetLeaveUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzMatchmakingLeaveNotificationEvent, FGs2MatchmakingLeaveNotification, Notification);

USTRUCT(BlueprintType)
struct FBpMatchmakingLeaveNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzMatchmakingLeaveNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingCompleteNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GatheringName = "";
};

inline FGs2MatchmakingCompleteNotification EzCompleteNotificationToFGs2MatchmakingCompleteNotification(
    const Gs2::Matchmaking::Model::FCompleteNotificationPtr Model
)
{
    FGs2MatchmakingCompleteNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.GatheringName = Model->GetGatheringName() ? *Model->GetGatheringName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzMatchmakingCompleteNotificationEvent, FGs2MatchmakingCompleteNotification, Notification);

USTRUCT(BlueprintType)
struct FBpMatchmakingCompleteNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzMatchmakingCompleteNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingChangeRatingNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString RatingName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    float RateValue = 0;
};

inline FGs2MatchmakingChangeRatingNotification EzChangeRatingNotificationToFGs2MatchmakingChangeRatingNotification(
    const Gs2::Matchmaking::Model::FChangeRatingNotificationPtr Model
)
{
    FGs2MatchmakingChangeRatingNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.RatingName = Model->GetRatingName() ? *Model->GetRatingName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RateValue = Model->GetRateValue() ? *Model->GetRateValue() : 0;
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzMatchmakingChangeRatingNotificationEvent, FGs2MatchmakingChangeRatingNotification, Notification);

USTRUCT(BlueprintType)
struct FBpMatchmakingChangeRatingNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzMatchmakingChangeRatingNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2MatchmakingFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Service", Category="Game Server Services|GS2-Matchmaking", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Matchmaking Service(
        FGs2Client Client,
        FBpMatchmakingJoinNotificationEvent JoinNotification,
        FBpMatchmakingLeaveNotificationEvent LeaveNotification,
        FBpMatchmakingCompleteNotificationEvent CompleteNotification,
        FBpMatchmakingChangeRatingNotificationEvent ChangeRatingNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Namespace", Category="Game Server Services|GS2-Matchmaking|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2MatchmakingNamespace Namespace(
        FGs2Matchmaking Service,
        FString NamespaceName
    );

};