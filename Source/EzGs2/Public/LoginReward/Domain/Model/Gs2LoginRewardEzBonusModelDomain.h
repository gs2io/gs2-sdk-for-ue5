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
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzVerifyAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzVerifyActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzTransactionResult.h"
#include "Gs2LoginRewardEzBonusModelDomain.h"
#include "LoginReward/Domain/Iterator/Gs2LoginRewardEzDescribeBonusModelsIterator.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzBonusModelDomain final :
        public TSharedFromThis<FEzBonusModelDomain>
    {
        Gs2::LoginReward::Domain::Model::FBonusModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> BonusModelName() const;

        FEzBonusModelDomain(
            Gs2::LoginReward::Domain::Model::FBonusModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Model::FEzBonusModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBonusModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBonusModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::LoginReward::Model::FEzBonusModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::LoginReward::Model::FEzBonusModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBonusModelDomain> FEzBonusModelDomainPtr;
}
