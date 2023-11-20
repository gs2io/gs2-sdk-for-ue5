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
#include "Friend/Model/Gs2FriendPublicProfile.h"
#include "Friend/Model/Gs2FriendPublicProfile.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendPublicProfileGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendPublicProfileGetValueSuccessDelegate, FGs2FriendPublicProfileValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendPublicProfileGetValueErrorDelegate, FGs2FriendPublicProfileValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendPublicProfileGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendPublicProfile PublicProfile;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendPublicProfileGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendPublicProfileGetValueErrorDelegate OnError;

    UGs2FriendPublicProfileGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Fetch::GetValueOfPublicProfile", Category="Game Server Services|GS2-Friend|Namespace|User|PublicProfile|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendPublicProfileGetValueAsyncFunction* PublicProfileGetValue(
        UObject* WorldContextObject,
        FGs2FriendPublicProfile PublicProfile
    );

    virtual void Activate() override;
};