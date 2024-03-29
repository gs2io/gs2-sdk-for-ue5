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
#include "News/Model/Gs2NewsUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "News/Model/Gs2NewsNews.h"
#include "Gs2NewsListOfNews.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsListOfNewsSuccessDelegate, const TArray<FGs2NewsNewsValue>, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsListOfNewsErrorDelegate, const TArray<FGs2NewsNewsValue>, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2NewsListOfNewsAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2NewsOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsListOfNewsSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsListOfNewsErrorDelegate OnError;

    UGs2NewsListOfNewsAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::News::Fetch::ListOfNews", Category="Game Server Services|GS2-News|Namespace|User|News|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2NewsListOfNewsAsyncFunction* ListOfNews(
        UObject* WorldContextObject,
        FGs2NewsOwnUser User
    );

    virtual void Activate() override;
};