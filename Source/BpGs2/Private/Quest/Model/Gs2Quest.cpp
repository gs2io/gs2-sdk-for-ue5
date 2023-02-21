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

#include "Quest/Model/Gs2Quest.h"
#include "BpGs2/Public/Quest/Model/Gs2QuestNamespace.h"
#include "BpGs2/Public/Quest/Model/Gs2QuestQuestModel.h"
#include "Core/BpGs2Constant.h"

FGs2Quest UGs2QuestFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2Quest Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->Quest;
    return Return;
}
FGs2QuestNamespace UGs2QuestFunctionLibrary::Namespace(
    FGs2Quest Service,
    FString NamespaceName
)
{
    FGs2QuestNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}