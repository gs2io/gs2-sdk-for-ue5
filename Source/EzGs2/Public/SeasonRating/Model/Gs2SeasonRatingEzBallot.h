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
#include "SeasonRating/Model/Ballot.h"

namespace Gs2::UE5::SeasonRating::Model
{
	class EZGS2_API FEzBallot final : public TSharedFromThis<FEzBallot>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> SeasonNameValue;
        TOptional<FString> SessionNameValue;
        TOptional<int32> NumberOfPlayerValue;

	public:
        TSharedPtr<FEzBallot> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzBallot> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FEzBallot> WithSessionName(const TOptional<FString> SessionName);
        TSharedPtr<FEzBallot> WithNumberOfPlayer(const TOptional<int32> NumberOfPlayer);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetSeasonName() const;

        TOptional<FString> GetSessionName() const;

        TOptional<int32> GetNumberOfPlayer() const;
        FString GetNumberOfPlayerString() const;

        Gs2::SeasonRating::Model::FBallotPtr ToModel() const;
        static TSharedPtr<FEzBallot> FromModel(Gs2::SeasonRating::Model::FBallotPtr Model);
    };
    typedef TSharedPtr<FEzBallot> FEzBallotPtr;
}