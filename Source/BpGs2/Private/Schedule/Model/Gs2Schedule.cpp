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

#include "Schedule/Model/Gs2Schedule.h"
#include "Schedule/Domain/EzGs2Schedule.h"
#include "Schedule/Model/Gs2ScheduleNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2Schedule UGs2ScheduleFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2Schedule Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->Schedule;
    return Return;
}
FGs2ScheduleNamespace UGs2ScheduleFunctionLibrary::Namespace(
    FGs2Schedule Service,
    FString NamespaceName
)
{
    FGs2ScheduleNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}