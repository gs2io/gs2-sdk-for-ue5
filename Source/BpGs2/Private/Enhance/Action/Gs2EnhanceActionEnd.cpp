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

#include "Enhance/Action/Gs2EnhanceActionEnd.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceEndAsyncFunction::UGs2EnhanceEndAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceEndAsyncFunction* UGs2EnhanceEndAsyncFunction::End(
    UObject* WorldContextObject,
    FGs2EnhanceOwnProgress Progress,
    TArray<FGs2EnhanceConfig> Config
)
{
    UGs2EnhanceEndAsyncFunction* Action = NewObject<UGs2EnhanceEndAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceEndAsyncFunction::End] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    Action->Config = Config;
    return Action;
}

void UGs2EnhanceEndAsyncFunction::Activate()
{
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceEndAsyncFunction] Progress parameter specification is missing."))
        return;
    }

    auto Future = Progress.Value->End(
        [&]
        {
            TArray<Gs2::UE5::Enhance::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2EnhanceConfigToEzConfig(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}