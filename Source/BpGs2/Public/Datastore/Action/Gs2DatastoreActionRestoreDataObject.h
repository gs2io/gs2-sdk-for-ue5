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
#include "Datastore/Model/Gs2DatastoreNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DatastoreActionRestoreDataObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreRestoreDataObjectSuccessDelegate, FGs2DatastoreDataObject, DataObject, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreRestoreDataObjectErrorDelegate, FGs2DatastoreDataObject, DataObject, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DatastoreRestoreDataObjectAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DatastoreNamespace Namespace;
    FString DataObjectId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreRestoreDataObjectSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreRestoreDataObjectErrorDelegate OnError;

    UGs2DatastoreRestoreDataObjectAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::DataObject::Action::RestoreDataObject", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DatastoreRestoreDataObjectAsyncFunction* RestoreDataObject(
        UObject* WorldContextObject,
        FGs2DatastoreNamespace Namespace,
        FString DataObjectId
    );

    virtual void Activate() override;
};