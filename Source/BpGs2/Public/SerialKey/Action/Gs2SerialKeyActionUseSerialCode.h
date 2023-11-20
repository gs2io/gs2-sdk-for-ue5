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
#include "SerialKey/Model/Gs2SerialKeySerialKey.h"
#include "SerialKey/Model/Gs2SerialKeySerialKey.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2SerialKeyActionUseSerialCode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SerialKeyUseSerialCodeSuccessDelegate, FGs2SerialKeyOwnSerialKey, SerialKey, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SerialKeyUseSerialCodeErrorDelegate, FGs2SerialKeyOwnSerialKey, SerialKey, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2SerialKeyUseSerialCodeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2SerialKeyOwnSerialKey SerialKey;
    FString Code;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SerialKeyUseSerialCodeSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SerialKeyUseSerialCodeErrorDelegate OnError;

    UGs2SerialKeyUseSerialCodeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::SerialKey::SerialKey::Action::UseSerialCode", Category="Game Server Services|GS2-SerialKey|Namespace|User|SerialKey|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2SerialKeyUseSerialCodeAsyncFunction* UseSerialCode(
        UObject* WorldContextObject,
        FGs2SerialKeyOwnSerialKey SerialKey,
        FString Code
    );

    virtual void Activate() override;
};