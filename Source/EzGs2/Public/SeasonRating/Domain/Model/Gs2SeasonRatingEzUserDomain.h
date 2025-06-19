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
#include "SeasonRating/Domain/Model/User.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSignedBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzVerifyActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzConsumeActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzAcquireActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTransactionResult.h"
#include "Gs2SeasonRatingEzBallotDomain.h"
#include "Gs2SeasonRatingEzUserDomain.h"
#include "Gs2SeasonRatingEzUserDomain.h"
#include "Gs2SeasonRatingEzUserGameSessionDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SeasonRating::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::SeasonRating::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::SeasonRating::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::SeasonRating::Domain::Model::FEzBallotDomainPtr Ballot(
            const FString SeasonName,
            const FString SessionName,
            const int32 NumberOfPlayer,
            const FString KeyId
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
