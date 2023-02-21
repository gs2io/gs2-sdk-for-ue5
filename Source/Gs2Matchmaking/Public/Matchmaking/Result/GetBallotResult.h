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

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FGetBallotResult final : public TSharedFromThis<FGetBallotResult>
    {
        TSharedPtr<Model::FBallot> ItemValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetBallotResult();
        FGetBallotResult(
            const FGetBallotResult& From
        );
        ~FGetBallotResult() = default;

        TSharedPtr<FGetBallotResult> WithItem(const TSharedPtr<Model::FBallot> Item);
        TSharedPtr<FGetBallotResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetBallotResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FBallot> GetItem() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetBallotResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBallotResult, ESPMode::ThreadSafe> FGetBallotResultPtr;
}