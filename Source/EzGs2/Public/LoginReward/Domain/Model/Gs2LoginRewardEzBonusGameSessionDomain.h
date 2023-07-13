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
#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "Gs2LoginRewardEzBonusGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzBonusGameSessionDomain final :
        public TSharedFromThis<FEzBonusGameSessionDomain>
    {
        Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzBonusGameSessionDomain(
            Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FReceiveTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            TSharedPtr<FEzBonusGameSessionDomain> Self;
            FString BonusModelName;
            TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config;

        public:
            explicit FReceiveTask(
                TSharedPtr<FEzBonusGameSessionDomain> Self,
                FString BonusModelName,
                TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
            FString BonusModelName,
            TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>>()
        );

        class FMissedReceiveTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>,
            public TSharedFromThis<FMissedReceiveTask>
        {
            TSharedPtr<FEzBonusGameSessionDomain> Self;
            FString BonusModelName;
            int32 StepNumber;
            TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config;

        public:
            explicit FMissedReceiveTask(
                TSharedPtr<FEzBonusGameSessionDomain> Self,
                FString BonusModelName,
                int32 StepNumber,
                TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>> Result
            ) override;
        };
        friend FMissedReceiveTask;

        TSharedPtr<FAsyncTask<FMissedReceiveTask>> MissedReceive(
            FString BonusModelName,
            int32 StepNumber,
            TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>>()
        );

    };
    typedef TSharedPtr<FEzBonusGameSessionDomain> FEzBonusGameSessionDomainPtr;
}
