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
#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"
#include "LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "Gs2LoginRewardEzReceiveStatusGameSessionDomain.h"
#include "LoginReward/Domain/Iterator/Gs2LoginRewardEzDescribeReceiveStatusesIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzReceiveStatusGameSessionDomain final :
        public TSharedFromThis<FEzReceiveStatusGameSessionDomain>
    {
        Gs2::LoginReward::Domain::Model::FReceiveStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> BonusModelName() const;

        FEzReceiveStatusGameSessionDomain(
            Gs2::LoginReward::Domain::Model::FReceiveStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetReceiveStatusTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Model::FEzReceiveStatus>,
            public TSharedFromThis<FGetReceiveStatusTask>
        {
            TSharedPtr<FEzReceiveStatusGameSessionDomain> Self;

        public:
            explicit FGetReceiveStatusTask(
                TSharedPtr<FEzReceiveStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReceiveStatus>> Result
            ) override;
        };
        friend FGetReceiveStatusTask;

        TSharedPtr<FAsyncTask<FGetReceiveStatusTask>> GetReceiveStatus(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Model::FEzReceiveStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzReceiveStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzReceiveStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReceiveStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzReceiveStatusGameSessionDomain> FEzReceiveStatusGameSessionDomainPtr;
}
