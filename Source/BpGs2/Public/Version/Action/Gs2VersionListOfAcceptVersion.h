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
#include "Version/Model/Gs2VersionUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2VersionListOfAcceptVersion.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionListOfAcceptVersionSuccessDelegate, const TArray<FGs2VersionAcceptVersionValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionListOfAcceptVersionErrorDelegate, const TArray<FGs2VersionAcceptVersionValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2VersionListOfAcceptVersionAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2VersionOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionListOfAcceptVersionSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionListOfAcceptVersionErrorDelegate OnError;

    UGs2VersionListOfAcceptVersionAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Version::Fetch::ListOfAcceptVersion", Category="Game Server Services|GS2-Version|Namespace|User|AcceptVersion|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2VersionListOfAcceptVersionAsyncFunction* ListOfAcceptVersion(
        UObject* WorldContextObject,
        FGs2VersionOwnUser User
    );

    virtual void Activate() override;
};