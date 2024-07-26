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
#include "Gs2Friend.generated.h"

USTRUCT(BlueprintType)
struct FGs2Friend
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::FEzGs2FriendPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendFollowNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString FromUserId = "";
};

inline FGs2FriendFollowNotification EzFollowNotificationToFGs2FriendFollowNotification(
    const Gs2::Friend::Model::FFollowNotificationPtr Model
)
{
    FGs2FriendFollowNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.FromUserId = Model->GetFromUserId() ? *Model->GetFromUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendFollowNotificationEvent, FGs2FriendFollowNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendFollowNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendFollowNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2FriendAcceptRequestNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetUserId = "";
};

inline FGs2FriendAcceptRequestNotification EzAcceptRequestNotificationToFGs2FriendAcceptRequestNotification(
    const Gs2::Friend::Model::FAcceptRequestNotificationPtr Model
)
{
    FGs2FriendAcceptRequestNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TargetUserId = Model->GetTargetUserId() ? *Model->GetTargetUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendAcceptRequestNotificationEvent, FGs2FriendAcceptRequestNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendAcceptRequestNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendAcceptRequestNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2FriendRejectRequestNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetUserId = "";
};

inline FGs2FriendRejectRequestNotification EzRejectRequestNotificationToFGs2FriendRejectRequestNotification(
    const Gs2::Friend::Model::FRejectRequestNotificationPtr Model
)
{
    FGs2FriendRejectRequestNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TargetUserId = Model->GetTargetUserId() ? *Model->GetTargetUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendRejectRequestNotificationEvent, FGs2FriendRejectRequestNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendRejectRequestNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendRejectRequestNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2FriendDeleteFriendNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString FromUserId = "";
};

inline FGs2FriendDeleteFriendNotification EzDeleteFriendNotificationToFGs2FriendDeleteFriendNotification(
    const Gs2::Friend::Model::FDeleteFriendNotificationPtr Model
)
{
    FGs2FriendDeleteFriendNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.FromUserId = Model->GetFromUserId() ? *Model->GetFromUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendDeleteFriendNotificationEvent, FGs2FriendDeleteFriendNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendDeleteFriendNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendDeleteFriendNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2FriendReceiveRequestNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString FromUserId = "";
};

inline FGs2FriendReceiveRequestNotification EzReceiveRequestNotificationToFGs2FriendReceiveRequestNotification(
    const Gs2::Friend::Model::FReceiveRequestNotificationPtr Model
)
{
    FGs2FriendReceiveRequestNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.FromUserId = Model->GetFromUserId() ? *Model->GetFromUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendReceiveRequestNotificationEvent, FGs2FriendReceiveRequestNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendReceiveRequestNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendReceiveRequestNotificationEvent Value;
};

USTRUCT(BlueprintType)
struct FGs2FriendCancelRequestNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString FromUserId = "";
};

inline FGs2FriendCancelRequestNotification EzCancelRequestNotificationToFGs2FriendCancelRequestNotification(
    const Gs2::Friend::Model::FCancelRequestNotificationPtr Model
)
{
    FGs2FriendCancelRequestNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.FromUserId = Model->GetFromUserId() ? *Model->GetFromUserId() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzFriendCancelRequestNotificationEvent, FGs2FriendCancelRequestNotification, Notification);

USTRUCT(BlueprintType)
struct FBpFriendCancelRequestNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzFriendCancelRequestNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2FriendFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Service", Category="Game Server Services|GS2-Friend", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Friend Service(
        FGs2Client Client,
        FBpFriendFollowNotificationEvent FollowNotification,
        FBpFriendAcceptRequestNotificationEvent AcceptRequestNotification,
        FBpFriendRejectRequestNotificationEvent RejectRequestNotification,
        FBpFriendDeleteFriendNotificationEvent DeleteFriendNotification,
        FBpFriendReceiveRequestNotificationEvent ReceiveRequestNotification,
        FBpFriendCancelRequestNotificationEvent CancelRequestNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Namespace", Category="Game Server Services|GS2-Friend|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2FriendNamespace Namespace(
        FGs2Friend Service,
        FString NamespaceName
    );

};