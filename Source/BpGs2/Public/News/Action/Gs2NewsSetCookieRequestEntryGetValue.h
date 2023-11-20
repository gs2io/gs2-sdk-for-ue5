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
#include "News/Model/Gs2NewsSetCookieRequestEntry.h"
#include "News/Model/Gs2NewsSetCookieRequestEntry.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2NewsSetCookieRequestEntryGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsSetCookieRequestEntryGetValueSuccessDelegate, FGs2NewsSetCookieRequestEntryValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2NewsSetCookieRequestEntryGetValueErrorDelegate, FGs2NewsSetCookieRequestEntryValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2NewsSetCookieRequestEntryGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2NewsOwnSetCookieRequestEntry SetCookieRequestEntry;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsSetCookieRequestEntryGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2NewsSetCookieRequestEntryGetValueErrorDelegate OnError;

    UGs2NewsSetCookieRequestEntryGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::News::Fetch::GetValueOfSetCookieRequestEntry", Category="Game Server Services|GS2-News|Namespace|User|SetCookieRequestEntry|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2NewsSetCookieRequestEntryGetValueAsyncFunction* SetCookieRequestEntryGetValue(
        UObject* WorldContextObject,
        FGs2NewsOwnSetCookieRequestEntry SetCookieRequestEntry
    );

    virtual void Activate() override;
};