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
#include "BpGs2/Public/SerialKey/Model/Gs2SerialKeySerialKey.h"
#include "BpGs2/Public/SerialKey/Model/Gs2SerialKeyUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2SerialKeySerialKeyGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SerialKeySerialKeyGetValueSuccessDelegate, FGs2SerialKeySerialKeyValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SerialKeySerialKeyGetValueErrorDelegate, FGs2SerialKeySerialKeyValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2SerialKeySerialKeyGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2SerialKeyUser User;

public:
    FString Code;

    UPROPERTY(BlueprintAssignable)
    FGs2SerialKeySerialKeyGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2SerialKeySerialKeyGetValueErrorDelegate OnError;

    UGs2SerialKeySerialKeyGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::Fetch::GetValueOfSerialKey", Category="Game Server Services|GS2-SerialKey|Namespace|User|SerialKey|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2SerialKeySerialKeyGetValueAsyncFunction* SerialKeyGetValue(
        UObject* WorldContextObject,
        FGs2SerialKeyUser User
    );

    virtual void Activate() override;
};