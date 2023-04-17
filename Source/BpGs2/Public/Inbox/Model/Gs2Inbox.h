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
#include "Gs2Inbox.generated.h"

USTRUCT(BlueprintType)
struct FGs2Inbox
{
    GENERATED_BODY()

    Gs2::UE5::Inbox::Domain::FEzGs2InboxPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InboxReceiveNotification
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(BlueprintReadWrite)
    FString MessageName = "";
};

inline FGs2InboxReceiveNotification EzReceiveNotificationToFGs2InboxReceiveNotification(
    const Gs2::Inbox::Model::FReceiveNotificationPtr Model
)
{
    FGs2InboxReceiveNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.MessageName = Model->GetMessageName() ? *Model->GetMessageName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzInboxReceiveNotificationEvent, FGs2InboxReceiveNotification, Notification);

USTRUCT(BlueprintType)
struct FBpInboxReceiveNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FEzInboxReceiveNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2InboxFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Service", Category="Game Server Services|GS2-Inbox", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Inbox Service(
        FGs2Client Client,
        FBpInboxReceiveNotificationEvent ReceiveNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Namespace", Category="Game Server Services|GS2-Inbox|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2InboxNamespace Namespace(
        FGs2Inbox Service,
        FString NamespaceName
    );

};