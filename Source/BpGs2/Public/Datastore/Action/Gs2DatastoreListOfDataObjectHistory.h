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
#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DatastoreListOfDataObjectHistory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreListOfDataObjectHistorySuccessDelegate, const TArray<FGs2DatastoreDataObjectHistoryValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreListOfDataObjectHistoryErrorDelegate, const TArray<FGs2DatastoreDataObjectHistoryValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DatastoreListOfDataObjectHistoryAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DatastoreOwnDataObject DataObject;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreListOfDataObjectHistorySuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreListOfDataObjectHistoryErrorDelegate OnError;

    UGs2DatastoreListOfDataObjectHistoryAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::Fetch::ListOfDataObjectHistory", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject|DataObjectHistory|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DatastoreListOfDataObjectHistoryAsyncFunction* ListOfDataObjectHistory(
        UObject* WorldContextObject,
        FGs2DatastoreOwnDataObject DataObject
    );

    virtual void Activate() override;
};