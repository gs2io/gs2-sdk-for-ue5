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
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "Gs2LoginRewardEzBonusModelDomain.h"
#include "LoginReward/Domain/Iterator/Gs2LoginRewardEzDescribeBonusModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzBonusModelDomain final :
        public TSharedFromThis<FEzBonusModelDomain>
    {
        Gs2::LoginReward::Domain::Model::FBonusModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> BonusModelName() const;

        FEzBonusModelDomain(
            Gs2::LoginReward::Domain::Model::FBonusModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetBonusModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Model::FEzBonusModel>,
            public TSharedFromThis<FGetBonusModelTask>
        {
            TSharedPtr<FEzBonusModelDomain> Self;

        public:
            explicit FGetBonusModelTask(
                TSharedPtr<FEzBonusModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzBonusModel>> Result
            ) override;
        };
        friend FGetBonusModelTask;

        TSharedPtr<FAsyncTask<FGetBonusModelTask>> GetBonusModel(
        );

        class FModelTask :
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

    };
    typedef TSharedPtr<FEzBonusModelDomain> FEzBonusModelDomainPtr;
}