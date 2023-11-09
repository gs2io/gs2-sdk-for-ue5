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
#include "Gs2AdReward.generated.h"

USTRUCT(BlueprintType)
struct FGs2AdReward
{
    GENERATED_BODY()

    Gs2::UE5::AdReward::Domain::FEzGs2AdRewardPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AdRewardChangePointNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
};

inline FGs2AdRewardChangePointNotification EzChangePointNotificationToFGs2AdRewardChangePointNotification(
    const Gs2::AdReward::Model::FChangePointNotificationPtr Model
)
{
    FGs2AdRewardChangePointNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzAdRewardChangePointNotificationEvent, FGs2AdRewardChangePointNotification, Notification);

USTRUCT(BlueprintType)
struct FBpAdRewardChangePointNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzAdRewardChangePointNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2AdRewardFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::AdReward::Service", Category="Game Server Services|GS2-AdReward", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2AdReward Service(
        FGs2Client Client,
        FBpAdRewardChangePointNotificationEvent ChangePointNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::AdReward::Namespace", Category="Game Server Services|GS2-AdReward|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2AdRewardNamespace Namespace(
        FGs2AdReward Service,
        FString NamespaceName
    );

};