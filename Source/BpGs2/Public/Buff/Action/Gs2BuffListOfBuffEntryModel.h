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
#include "Buff/Model/Gs2BuffNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2BuffListOfBuffEntryModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2BuffListOfBuffEntryModelSuccessDelegate, const TArray<FGs2BuffBuffEntryModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2BuffListOfBuffEntryModelErrorDelegate, const TArray<FGs2BuffBuffEntryModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2BuffListOfBuffEntryModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2BuffNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2BuffListOfBuffEntryModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2BuffListOfBuffEntryModelErrorDelegate OnError;

    UGs2BuffListOfBuffEntryModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Buff::Fetch::ListOfBuffEntryModel", Category="Game Server Services|GS2-Buff|Namespace|BuffEntryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2BuffListOfBuffEntryModelAsyncFunction* ListOfBuffEntryModel(
        UObject* WorldContextObject,
        FGs2BuffNamespace Namespace
    );

    virtual void Activate() override;
};