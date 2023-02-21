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
#include "BpGs2/Public/Dictionary/Model/Gs2DictionaryEntry.h"
#include "BpGs2/Public/Dictionary/Model/Gs2DictionaryEntry.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DictionaryEntryGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryEntryGetValueSuccessDelegate, FGs2DictionaryEntryValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryEntryGetValueErrorDelegate, FGs2DictionaryEntryValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DictionaryEntryGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DictionaryOwnEntry Entry;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2DictionaryEntryGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2DictionaryEntryGetValueErrorDelegate OnError;

    UGs2DictionaryEntryGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Dictionary::Fetch::GetValueOfEntry", Category="Game Server Services|GS2-Dictionary|Namespace|User|Entry|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DictionaryEntryGetValueAsyncFunction* EntryGetValue(
        UObject* WorldContextObject,
        FGs2DictionaryOwnEntry Entry
    );

    virtual void Activate() override;
};