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

#include "MegaField/Action/Gs2MegaFieldActionUpdate.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldUpdateAsyncFunction::UGs2MegaFieldUpdateAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldUpdateAsyncFunction* UGs2MegaFieldUpdateAsyncFunction::Update(
    UObject* WorldContextObject,
    FGs2MegaFieldOwnSpatial Spatial,
    FGs2MegaFieldMyPosition Position,
    TArray<FGs2MegaFieldScope> Scopes
)
{
    UGs2MegaFieldUpdateAsyncFunction* Action = NewObject<UGs2MegaFieldUpdateAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Spatial.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldUpdateAsyncFunction::Update] Spatial parameter specification is missing."))
        return Action;
    }
    Action->Spatial = Spatial;
    Action->Position = Position;
    Action->Scopes = Scopes;
    return Action;
}

void UGs2MegaFieldUpdateAsyncFunction::Activate()
{
    if (Spatial.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldUpdateAsyncFunction] Spatial parameter specification is missing."))
        return;
    }

    auto Future = Spatial.Value->Update(
        FGs2MegaFieldMyPositionToEzMyPosition(Position),
        [&]
        {
            TArray<Gs2::UE5::MegaField::Model::FEzScopePtr> r;
            for (auto v : Scopes)
            {
                r.Add(FGs2MegaFieldScopeToEzScope(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        TArray<FGs2MegaFieldSpatial> ReturnSpatial;
        for (int i=0; i<Result->Num(); i++)
        {
            FGs2MegaFieldSpatial r;
            r.Value = (*Result)[i];
            ReturnSpatial.Add(r);
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSpatial, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2MegaFieldSpatial> ReturnSpatial;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSpatial, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}