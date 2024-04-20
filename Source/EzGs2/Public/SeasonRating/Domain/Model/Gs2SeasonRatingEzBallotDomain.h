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
#include "SeasonRating/Domain/Model/Ballot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSignedBallot.h"
#include "Gs2SeasonRatingEzBallotDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SeasonRating::Domain::Model
{

    class EZGS2_API FEzBallotDomain final :
        public TSharedFromThis<FEzBallotDomain>
    {
        Gs2::SeasonRating::Domain::Model::FBallotDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> SeasonName() const;
        TOptional<FString> SessionName() const;
        TOptional<int32> NumberOfPlayer() const;
        TOptional<FString> KeyId() const;

        FEzBallotDomain(
            Gs2::SeasonRating::Domain::Model::FBallotDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SeasonRating::Model::FEzBallot>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBallotDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBallotDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzBallotPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::SeasonRating::Model::FEzBallotPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBallotDomain> FEzBallotDomainPtr;
}