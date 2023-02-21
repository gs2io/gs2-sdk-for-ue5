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
#include "Matchmaking/Model/SignedBallot.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzSignedBallot final : public TSharedFromThis<FEzSignedBallot>
	{
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;

	public:
        TSharedPtr<FEzSignedBallot> WithBody(const TOptional<FString> Body);
        TSharedPtr<FEzSignedBallot> WithSignature(const TOptional<FString> Signature);

        TOptional<FString> GetBody() const;

        TOptional<FString> GetSignature() const;

        Gs2::Matchmaking::Model::FSignedBallotPtr ToModel() const;
        static TSharedPtr<FEzSignedBallot> FromModel(Gs2::Matchmaking::Model::FSignedBallotPtr Model);
    };
    typedef TSharedPtr<FEzSignedBallot> FEzSignedBallotPtr;
}