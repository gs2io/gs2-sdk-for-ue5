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

#include "Ranking/Model/Gs2Ranking.h"
#include "Ranking/Domain/EzGs2Ranking.h"
#include "Ranking/Model/Gs2RankingNamespace.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Core/BpGs2Constant.h"

FGs2Ranking UGs2RankingFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2Ranking Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->Ranking;
    return Return;
}
FGs2RankingNamespace UGs2RankingFunctionLibrary::Namespace(
    FGs2Ranking Service,
    FString NamespaceName
)
{
    FGs2RankingNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}