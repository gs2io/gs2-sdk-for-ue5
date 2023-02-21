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

#include "Version/Action/Gs2VersionActionCheckVersion.h"
#include "Core/BpGs2Constant.h"

UGs2VersionCheckVersionAsyncFunction::UGs2VersionCheckVersionAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2VersionCheckVersionAsyncFunction* UGs2VersionCheckVersionAsyncFunction::CheckVersion(
    UObject* WorldContextObject,
    FGs2VersionOwnChecker Checker,
    TArray<FGs2VersionTargetVersion> TargetVersions
)
{
    UGs2VersionCheckVersionAsyncFunction* Action = NewObject<UGs2VersionCheckVersionAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Checker.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionCheckVersionAsyncFunction::CheckVersion] Checker parameter specification is missing."))
        return Action;
    }
    Action->Checker = Checker;
    Action->TargetVersions = TargetVersions;
    return Action;
}

void UGs2VersionCheckVersionAsyncFunction::Activate()
{
    if (Checker.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionCheckVersionAsyncFunction] Checker parameter specification is missing."))
        return;
    }

    auto Future = Checker.Value->CheckVersion(
        [&]
        {
            TArray<Gs2::UE5::Version::Model::FEzTargetVersionPtr> r;
            for (auto v : TargetVersions)
            {
                r.Add(FGs2VersionTargetVersionToEzTargetVersion(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2VersionOwnChecker ReturnChecker;
        ReturnChecker.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnChecker, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2VersionOwnChecker ReturnChecker;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnChecker, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}