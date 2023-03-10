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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Model/Gs2QuestEzContents.h"
#include "Quest/Model/Gs2QuestEzConsumeAction.h"
#include "Quest/Model/Gs2QuestEzAcquireAction.h"
#include "Quest/Model/Gs2QuestEzReward.h"
#include "Quest/Model/Gs2QuestEzConfig.h"
#include "Quest/Model/Gs2QuestEzProgress.h"
#include "Quest/Model/Gs2QuestEzCompletedQuestList.h"
#include "Quest/Model/Gs2QuestEzQuestGroupModel.h"
#include "Quest/Model/Gs2QuestEzQuestModel.h"
#include "Gs2QuestEzProgressGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzProgressGameSessionDomain final :
        public TSharedFromThis<FEzProgressGameSessionDomain>
    {
        Gs2::Quest::Domain::Model::FProgressAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzProgressGameSessionDomain(
            Gs2::Quest::Domain::Model::FProgressAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetProgressTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzProgress>,
            public TSharedFromThis<FGetProgressTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;

        public:
            explicit FGetProgressTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzProgress>> Result
            ) override;
        };
        friend FGetProgressTask;

        TSharedPtr<FAsyncTask<FGetProgressTask>> GetProgress(
        );

        class FEndTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FEndTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;
            bool IsComplete_;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config;

        public:
            explicit FEndTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self,
                bool IsComplete,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            bool IsComplete,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzProgress>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Quest::Model::FEzProgressPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzProgressGameSessionDomain> FEzProgressGameSessionDomainPtr;
}
