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
#include "Gs2JobQueue.generated.h"

USTRUCT(BlueprintType)
struct FGs2JobQueue
{
    GENERATED_BODY()

    Gs2::UE5::JobQueue::Domain::FEzGs2JobQueuePtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2JobQueuePushNotification
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString NamespaceName = "";
};

inline FGs2JobQueuePushNotification EzPushNotificationToFGs2JobQueuePushNotification(
    const Gs2::JobQueue::Model::FPushNotificationPtr Model
)
{
    FGs2JobQueuePushNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzJobQueuePushNotificationEvent, FGs2JobQueuePushNotification, Notification);

USTRUCT(BlueprintType)
struct FBpJobQueuePushNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FEzJobQueuePushNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2JobQueueRunNotification
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(BlueprintReadWrite)
    FString JobName = "";
};

inline FGs2JobQueueRunNotification EzRunNotificationToFGs2JobQueueRunNotification(
    const Gs2::JobQueue::Model::FRunNotificationPtr Model
)
{
    FGs2JobQueueRunNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.JobName = Model->GetJobName() ? *Model->GetJobName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzJobQueueRunNotificationEvent, FGs2JobQueueRunNotification, Notification);

USTRUCT(BlueprintType)
struct FBpJobQueueRunNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FEzJobQueueRunNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2JobQueueFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::JobQueue::Service", Category="Game Server Services|GS2-JobQueue", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2JobQueue Service(
        FGs2Client Client,
        FBpJobQueuePushNotificationEvent PushNotification,
        FBpJobQueueRunNotificationEvent RunNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::JobQueue::Namespace", Category="Game Server Services|GS2-JobQueue|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2JobQueueNamespace Namespace(
        FGs2JobQueue Service,
        FString NamespaceName
    );

};