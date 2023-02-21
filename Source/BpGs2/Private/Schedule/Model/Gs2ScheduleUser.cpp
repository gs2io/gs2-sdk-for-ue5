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

#include "BpGs2/Public/Schedule/Model/Gs2ScheduleUser.h"
#include "BpGs2/Public/Schedule/Model/Gs2ScheduleTrigger.h"
#include "BpGs2/Public/Schedule/Model/Gs2ScheduleEvent.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Schedule/Model/Gs2ScheduleTrigger.h"
#include "Schedule/Model/Gs2ScheduleEvent.h"
#include "Core/BpGs2Constant.h"

FGs2ScheduleOwnTrigger UGs2ScheduleUserFunctionLibrary::OwnTrigger(
    FGs2ScheduleOwnUser User,
    FString TriggerName
)
{
    FGs2ScheduleOwnTrigger Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleUserFunctionLibrary::OwnTrigger] User parameter specification is missing."))
        return Return;
    }
    if (TriggerName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleUserFunctionLibrary::OwnTrigger] TriggerName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Trigger(
        TriggerName
    );
    return Return;
}

FGs2ScheduleOwnEvent UGs2ScheduleUserFunctionLibrary::OwnEvent(
    FGs2ScheduleOwnUser User,
    FString EventName
)
{
    FGs2ScheduleOwnEvent Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleUserFunctionLibrary::OwnEvent] User parameter specification is missing."))
        return Return;
    }
    if (EventName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleUserFunctionLibrary::OwnEvent] EventName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Event(
        EventName
    );
    return Return;
}