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
#include "News/Model/Gs2NewsSetCookieRequestEntry.h"
#include "News/Model/Gs2NewsNews.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "News/Model/Gs2NewsUser.h"
#include "Gs2NewsActionGetContentsUrl.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsGetContentsUrlSuccessDelegate, const TArray<FGs2NewsOwnSetCookieRequestEntry>, SetCookieRequestEntries, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsGetContentsUrlErrorDelegate, const TArray<FGs2NewsOwnSetCookieRequestEntry>, SetCookieRequestEntries, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2NewsGetContentsUrlAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2NewsOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsGetContentsUrlSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsGetContentsUrlErrorDelegate OnError;

    UGs2NewsGetContentsUrlAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::News::News::Action::GetContentsUrl", Category="Game Server Services|GS2-News|Namespace|User|News|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2NewsGetContentsUrlAsyncFunction* GetContentsUrl(
        UObject* WorldContextObject,
        FGs2NewsOwnUser User
    );

    virtual void Activate() override;
};