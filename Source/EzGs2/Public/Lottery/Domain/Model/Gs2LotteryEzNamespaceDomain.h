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
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"
#include "Lottery/Model/Gs2LotteryEzProbability.h"
#include "Lottery/Model/Gs2LotteryEzAcquireAction.h"
#include "Lottery/Model/Gs2LotteryEzDrawnPrize.h"
#include "Lottery/Model/Gs2LotteryEzBoxItem.h"
#include "Lottery/Model/Gs2LotteryEzBoxItems.h"
#include "Lottery/Model/Gs2LotteryEzConfig.h"
#include "Gs2LotteryEzUserDomain.h"
#include "Gs2LotteryEzUserDomain.h"
#include "Gs2LotteryEzUserGameSessionDomain.h"
#include "Gs2LotteryEzLotteryModelDomain.h"
#include "Lottery/Domain/Iterator/Gs2LotteryEzDescribeLotteryModelsIterator.h"
#include "Gs2LotteryEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Lottery::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Lottery::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Lottery::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Lottery::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

        Gs2::UE5::Lottery::Domain::Iterator::FEzDescribeLotteryModelsIteratorPtr LotteryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLotteryModels(TFunction<void()> Callback);

        void UnsubscribeLotteryModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Lottery::Domain::Model::FEzLotteryModelDomainPtr LotteryModel(
            const FString LotteryName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
