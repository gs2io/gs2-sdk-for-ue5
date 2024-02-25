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

#pragma once

#include "CoreMinimal.h"

#include "SeasonRating/Model/Gs2SeasonRatingEzSignedBallot.h"
#include "Gs2SeasonRatingSignedBallot.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingSignedBallot
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Body = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Signature = "";
};

inline FGs2SeasonRatingSignedBallot EzSignedBallotToFGs2SeasonRatingSignedBallot(
    const Gs2::UE5::SeasonRating::Model::FEzSignedBallotPtr Model
)
{
    FGs2SeasonRatingSignedBallot Value;
    Value.Body = Model->GetBody() ? *Model->GetBody() : "";
    Value.Signature = Model->GetSignature() ? *Model->GetSignature() : "";
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzSignedBallotPtr FGs2SeasonRatingSignedBallotToEzSignedBallot(
    const FGs2SeasonRatingSignedBallot Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzSignedBallot>()
        ->WithBody(Model.Body)
        ->WithSignature(Model.Signature);
}