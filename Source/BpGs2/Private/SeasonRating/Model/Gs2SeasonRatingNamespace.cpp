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

#include "SeasonRating/Model/Gs2SeasonRatingNamespace.h"
#include "SeasonRating/Domain/EzGs2SeasonRating.h"
#include "SeasonRating/Model/Gs2SeasonRatingSeasonModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "SeasonRating/Model/Gs2SeasonRatingSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingUser.h"
#include "Core/BpGs2Constant.h"

FGs2SeasonRatingSeasonModel UGs2SeasonRatingNamespaceFunctionLibrary::SeasonModel(
    FGs2SeasonRatingNamespace Namespace,
    FString SeasonName
)
{
    FGs2SeasonRatingSeasonModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingNamespaceFunctionLibrary::SeasonModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (SeasonName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingNamespaceFunctionLibrary::SeasonModel] SeasonName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->SeasonModel(
        SeasonName
    );
    return Return;
}

FGs2SeasonRatingOwnUser UGs2SeasonRatingNamespaceFunctionLibrary::Me(
    FGs2SeasonRatingNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2SeasonRatingOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}