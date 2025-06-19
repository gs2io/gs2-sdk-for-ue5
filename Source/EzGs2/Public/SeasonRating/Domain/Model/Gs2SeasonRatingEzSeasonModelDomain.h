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
#include "SeasonRating/Domain/Model/SeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSignedBallot.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzVerifyActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzConsumeActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzAcquireActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzTransactionResult.h"
#include "Gs2SeasonRatingEzSeasonModelDomain.h"
#include "SeasonRating/Domain/Iterator/Gs2SeasonRatingEzDescribeSeasonModelsIterator.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::SeasonRating::Domain::Model
{

    class EZGS2_API FEzSeasonModelDomain final :
        public TSharedFromThis<FEzSeasonModelDomain>
    {
        Gs2::SeasonRating::Domain::Model::FSeasonModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> SeasonName() const;

        FEzSeasonModelDomain(
            Gs2::SeasonRating::Domain::Model::FSeasonModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SeasonRating::Model::FEzSeasonModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSeasonModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSeasonModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzSeasonModelDomain> FEzSeasonModelDomainPtr;
}
