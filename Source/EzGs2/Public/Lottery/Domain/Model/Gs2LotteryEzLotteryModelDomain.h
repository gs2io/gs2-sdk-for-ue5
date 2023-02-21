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
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"
#include "Lottery/Model/Gs2LotteryEzProbability.h"
#include "Lottery/Model/Gs2LotteryEzAcquireAction.h"
#include "Lottery/Model/Gs2LotteryEzDrawnPrize.h"
#include "Lottery/Model/Gs2LotteryEzBoxItem.h"
#include "Lottery/Model/Gs2LotteryEzBoxItems.h"
#include "Lottery/Model/Gs2LotteryEzConfig.h"
#include "Gs2LotteryEzLotteryModelDomain.h"
#include "Lottery/Domain/Iterator/Gs2LotteryEzDescribeLotteryModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    class EZGS2_API FEzLotteryModelDomain final :
        public TSharedFromThis<FEzLotteryModelDomain>
    {
        Gs2::Lottery::Domain::Model::FLotteryModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> LotteryName() const;

        FEzLotteryModelDomain(
            Gs2::Lottery::Domain::Model::FLotteryModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetLotteryModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Model::FEzLotteryModel>,
            public TSharedFromThis<FGetLotteryModelTask>
        {
            TSharedPtr<FEzLotteryModelDomain> Self;

        public:
            explicit FGetLotteryModelTask(
                TSharedPtr<FEzLotteryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzLotteryModel>> Result
            ) override;
        };
        friend FGetLotteryModelTask;

        TSharedPtr<FAsyncTask<FGetLotteryModelTask>> GetLotteryModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Model::FEzLotteryModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzLotteryModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzLotteryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Lottery::Model::FEzLotteryModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzLotteryModelDomain> FEzLotteryModelDomainPtr;
}
