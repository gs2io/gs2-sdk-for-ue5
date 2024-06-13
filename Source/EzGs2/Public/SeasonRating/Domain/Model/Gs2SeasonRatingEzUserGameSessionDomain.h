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
#include "SeasonRating/Domain/Model/UserAccessToken.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSignedBallot.h"
#include "Gs2SeasonRatingEzBallotGameSessionDomain.h"
#include "Gs2SeasonRatingEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SeasonRating::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::SeasonRating::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::SeasonRating::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::SeasonRating::Domain::Model::FEzBallotGameSessionDomainPtr Ballot(
            const FString SeasonName,
            const FString SessionName,
            const int32 NumberOfPlayer,
            const FString KeyId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
