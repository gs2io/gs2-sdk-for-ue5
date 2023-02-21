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

#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingNamespace.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingRatingModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Matchmaking/Model/Gs2MatchmakingUser.h"
#include "Matchmaking/Model/Gs2MatchmakingRatingModel.h"
#include "Core/BpGs2Constant.h"

FGs2MatchmakingUser UGs2MatchmakingNamespaceFunctionLibrary::User(
    FGs2MatchmakingNamespace Namespace,
    FString UserId
)
{
    FGs2MatchmakingUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::User] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::User] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->User(
        UserId
    );
    return Return;
}

FGs2MatchmakingOwnUser UGs2MatchmakingNamespaceFunctionLibrary::Me(
    FGs2MatchmakingNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2MatchmakingOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}

FGs2MatchmakingRatingModel UGs2MatchmakingNamespaceFunctionLibrary::RatingModel(
    FGs2MatchmakingNamespace Namespace,
    FString RatingName
)
{
    FGs2MatchmakingRatingModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::RatingModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (RatingName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingNamespaceFunctionLibrary::RatingModel] RatingName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->RatingModel(
        RatingName
    );
    return Return;
}