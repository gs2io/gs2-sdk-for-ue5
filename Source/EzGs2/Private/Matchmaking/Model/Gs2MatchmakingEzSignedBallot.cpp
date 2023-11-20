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

#include "Matchmaking/Model/Gs2MatchmakingEzSignedBallot.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzSignedBallot> FEzSignedBallot::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FEzSignedBallot> FEzSignedBallot::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }
    TOptional<FString> FEzSignedBallot::GetBody() const
    {
        return BodyValue;
    }
    TOptional<FString> FEzSignedBallot::GetSignature() const
    {
        return SignatureValue;
    }

    Gs2::Matchmaking::Model::FSignedBallotPtr FEzSignedBallot::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FSignedBallot>()
            ->WithBody(BodyValue)
            ->WithSignature(SignatureValue);
    }

    TSharedPtr<FEzSignedBallot> FEzSignedBallot::FromModel(const Gs2::Matchmaking::Model::FSignedBallotPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSignedBallot>()
            ->WithBody(Model->GetBody())
            ->WithSignature(Model->GetSignature());
    }
}