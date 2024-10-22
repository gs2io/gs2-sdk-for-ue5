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

#include "SeasonRating/Model/Gs2SeasonRatingUser.h"
#include "SeasonRating/Domain/EzGs2SeasonRating.h"
#include "SeasonRating/Model/Gs2SeasonRatingBallot.h"
#include "Core/Model/Gs2AccessToken.h"
#include "SeasonRating/Model/Gs2SeasonRatingBallot.h"
#include "Core/BpGs2Constant.h"

FGs2SeasonRatingOwnBallot UGs2SeasonRatingUserFunctionLibrary::OwnBallot(
    FGs2SeasonRatingOwnUser User,
    FString SeasonName,
    FString SessionName,
    int32 NumberOfPlayer,
    FString KeyId
)
{
    FGs2SeasonRatingOwnBallot Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingUserFunctionLibrary::OwnBallot] User parameter specification is missing."))
        return Return;
    }
    if (SeasonName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingUserFunctionLibrary::OwnBallot] SeasonName parameter specification is missing."))
        return Return;
    }
    if (SessionName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingUserFunctionLibrary::OwnBallot] SessionName parameter specification is missing."))
        return Return;
    }
    if (KeyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingUserFunctionLibrary::OwnBallot] KeyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Ballot(
        SeasonName,
        SessionName,
        NumberOfPlayer,
        KeyId
    );
    return Return;
}