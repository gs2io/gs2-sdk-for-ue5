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
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"
#include "Lottery/Model/Gs2LotteryEzProbability.h"
#include "Lottery/Model/Gs2LotteryEzAcquireAction.h"
#include "Lottery/Model/Gs2LotteryEzDrawnPrize.h"
#include "Lottery/Model/Gs2LotteryEzBoxItem.h"
#include "Lottery/Model/Gs2LotteryEzBoxItems.h"
#include "Lottery/Model/Gs2LotteryEzConfig.h"
#include "Lottery/Model/Gs2LotteryEzVerifyActionResult.h"
#include "Lottery/Model/Gs2LotteryEzConsumeActionResult.h"
#include "Lottery/Model/Gs2LotteryEzAcquireActionResult.h"
#include "Lottery/Model/Gs2LotteryEzTransactionResult.h"
#include "Gs2LotteryEzBoxItemsGameSessionDomain.h"
#include "Lottery/Domain/Iterator/Gs2LotteryEzDescribeBoxesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    class EZGS2_API FEzBoxItemsGameSessionDomain final :
        public TSharedFromThis<FEzBoxItemsGameSessionDomain>
    {
        Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> PrizeTableName() const;

        FEzBoxItemsGameSessionDomain(
            Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FResetBoxTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>,
            public TSharedFromThis<FResetBoxTask>
        {
            TSharedPtr<FEzBoxItemsGameSessionDomain> Self;

        public:
            explicit FResetBoxTask(
                TSharedPtr<FEzBoxItemsGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>> Result
            ) override;
        };
        friend FResetBoxTask;

        TSharedPtr<FAsyncTask<FResetBoxTask>> ResetBox(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Model::FEzBoxItems>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBoxItemsGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBoxItemsGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItemsPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Lottery::Model::FEzBoxItemsPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBoxItemsGameSessionDomain> FEzBoxItemsGameSessionDomainPtr;
}
