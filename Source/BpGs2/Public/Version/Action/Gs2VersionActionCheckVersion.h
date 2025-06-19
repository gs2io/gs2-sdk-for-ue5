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
#include "Version/Model/Gs2VersionTargetVersion.h"
#include "Version/Model/Gs2VersionChecker.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2VersionActionCheckVersion.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionCheckVersionSuccessDelegate, FGs2VersionOwnChecker, Checker, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2VersionCheckVersionErrorDelegate, FGs2VersionOwnChecker, Checker, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2VersionCheckVersionAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2VersionOwnChecker Checker;
    TArray<FGs2VersionTargetVersion> TargetVersions;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionCheckVersionSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2VersionCheckVersionErrorDelegate OnError;

    UGs2VersionCheckVersionAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Version::Checker::Action::CheckVersion", Category="Game Server Services|GS2-Version|Namespace|User|Checker|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2VersionCheckVersionAsyncFunction* CheckVersion(
        UObject* WorldContextObject,
        FGs2VersionOwnChecker Checker,
        TArray<FGs2VersionTargetVersion> TargetVersions
    );

    virtual void Activate() override;
};