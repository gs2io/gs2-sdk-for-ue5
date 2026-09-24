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
#include "Money2/Model/Gs2Money2Namespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2Money2ListOfStoreContentModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2ListOfStoreContentModelSuccessDelegate, const TArray<FGs2Money2StoreContentModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2ListOfStoreContentModelErrorDelegate, const TArray<FGs2Money2StoreContentModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2Money2ListOfStoreContentModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2Money2Namespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2ListOfStoreContentModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2ListOfStoreContentModelErrorDelegate OnError;

    UGs2Money2ListOfStoreContentModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::Fetch::ListOfStoreContentModel", Category="Game Server Services|GS2-Money2|Namespace|StoreContentModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2Money2ListOfStoreContentModelAsyncFunction* ListOfStoreContentModel(
        UObject* WorldContextObject,
        FGs2Money2Namespace Namespace
    );

    virtual void Activate() override;
};