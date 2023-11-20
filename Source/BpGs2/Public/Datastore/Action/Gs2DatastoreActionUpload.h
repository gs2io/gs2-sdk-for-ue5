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
#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "Datastore/Model/Gs2DatastoreUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DatastoreActionUpload.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreUploadSuccessDelegate, FGs2DatastoreOwnDataObject, DataObject, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DatastoreUploadErrorDelegate, FGs2DatastoreOwnDataObject, DataObject, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DatastoreUploadAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DatastoreOwnUser User;
    TArray<uint8> Binary;
    FString Name;
    FString Scope;
    FString ContentType;
    TArray<FString> AllowUserIds;
    bool UpdateIfExists;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreUploadSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DatastoreUploadErrorDelegate OnError;

    UGs2DatastoreUploadAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::DataObject::Action::Upload", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DatastoreUploadAsyncFunction* Upload(
        UObject* WorldContextObject,
        FGs2DatastoreOwnUser User,
        TArray<uint8> Binary,
        FString Name,
        FString Scope,
        FString ContentType,
        TArray<FString> AllowUserIds,
        bool UpdateIfExists
    );

    virtual void Activate() override;
};