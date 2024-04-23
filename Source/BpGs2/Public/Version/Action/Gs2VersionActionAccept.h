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
#include "Version/Model/Gs2VersionAcceptVersion.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Version/Model/Gs2VersionAcceptVersion.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2VersionActionAccept.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionAcceptSuccessDelegate, FGs2VersionOwnAcceptVersion, AcceptVersion, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionAcceptErrorDelegate, FGs2VersionOwnAcceptVersion, AcceptVersion, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2VersionAcceptAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2VersionOwnAcceptVersion AcceptVersion;
    FGs2VersionVersion Version;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionAcceptSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionAcceptErrorDelegate OnError;

    UGs2VersionAcceptAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Version::AcceptVersion::Action::Accept", Category="Game Server Services|GS2-Version|Namespace|User|AcceptVersion|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2VersionAcceptAsyncFunction* Accept(
        UObject* WorldContextObject,
        FGs2VersionOwnAcceptVersion AcceptVersion,
        FGs2VersionVersion Version
    );

    virtual void Activate() override;
};