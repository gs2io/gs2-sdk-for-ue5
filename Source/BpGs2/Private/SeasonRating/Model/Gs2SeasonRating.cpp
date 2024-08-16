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

#include "SeasonRating/Model/Gs2SeasonRating.h"
#include "SeasonRating/Domain/EzGs2SeasonRating.h"
#include "SeasonRating/Model/Gs2SeasonRatingNamespace.h"
#include "SeasonRating/Model/Gs2SeasonRatingBallot.h"
#include "Core/BpGs2Constant.h"

FGs2SeasonRating UGs2SeasonRatingFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2SeasonRating Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->SeasonRating;
    return Return;
}
FGs2SeasonRatingNamespace UGs2SeasonRatingFunctionLibrary::Namespace(
    FGs2SeasonRating Service,
    FString NamespaceName
)
{
    FGs2SeasonRatingNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}