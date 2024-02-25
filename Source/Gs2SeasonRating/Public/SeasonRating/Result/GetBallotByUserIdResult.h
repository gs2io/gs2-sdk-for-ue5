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
#include "../Model/Ballot.h"

namespace Gs2::SeasonRating::Result
{
    class GS2SEASONRATING_API FGetBallotByUserIdResult final : public TSharedFromThis<FGetBallotByUserIdResult>
    {
        TSharedPtr<Model::FBallot> ItemValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetBallotByUserIdResult();
        FGetBallotByUserIdResult(
            const FGetBallotByUserIdResult& From
        );
        ~FGetBallotByUserIdResult() = default;

        TSharedPtr<FGetBallotByUserIdResult> WithItem(const TSharedPtr<Model::FBallot> Item);
        TSharedPtr<FGetBallotByUserIdResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetBallotByUserIdResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FBallot> GetItem() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetBallotByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBallotByUserIdResult, ESPMode::ThreadSafe> FGetBallotByUserIdResultPtr;
}