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
#include "Datastore/Domain/Model/Gs2DatastoreEzUserGameSessionDomain.h"
#include "Datastore/Domain/Model/Gs2DatastoreEzUserDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2DatastoreUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2DatastoreOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Datastore::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2DatastoreUser
{
    GENERATED_BODY()

    Gs2::UE5::Datastore::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2DatastoreUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::DataObject", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="DataObject") FGs2DatastoreDataObject DataObject(
        FGs2DatastoreUser User,
        FString DataObjectName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Datastore::OwnDataObject", Category="Game Server Services|GS2-Datastore|Namespace|User|DataObject", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="DataObject") FGs2DatastoreOwnDataObject OwnDataObject(
        FGs2DatastoreOwnUser User,
        FString DataObjectName
    );
};