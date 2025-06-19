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
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Model/Gs2QuestEzContents.h"
#include "Quest/Model/Gs2QuestEzConsumeAction.h"
#include "Quest/Model/Gs2QuestEzVerifyAction.h"
#include "Quest/Model/Gs2QuestEzAcquireAction.h"
#include "Quest/Model/Gs2QuestEzReward.h"
#include "Quest/Model/Gs2QuestEzConfig.h"
#include "Quest/Model/Gs2QuestEzProgress.h"
#include "Quest/Model/Gs2QuestEzCompletedQuestList.h"
#include "Quest/Model/Gs2QuestEzQuestGroupModel.h"
#include "Quest/Model/Gs2QuestEzQuestModel.h"
#include "Quest/Model/Gs2QuestEzVerifyActionResult.h"
#include "Quest/Model/Gs2QuestEzConsumeActionResult.h"
#include "Quest/Model/Gs2QuestEzAcquireActionResult.h"
#include "Quest/Model/Gs2QuestEzTransactionResult.h"
#include "Gs2QuestEzProgressGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzProgressGameSessionDomain final :
        public TSharedFromThis<FEzProgressGameSessionDomain>
    {
        Gs2::Quest::Domain::Model::FProgressAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzProgressGameSessionDomain(
            Gs2::Quest::Domain::Model::FProgressAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FEndTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>,
            public TSharedFromThis<FEndTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;
            bool IsComplete;
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
                TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            bool IsComplete,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
        );

        class EZGS2_API FDeleteProgressTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FDeleteProgressTask>
        {
            TSharedPtr<FEzProgressGameSessionDomain> Self;

        public:
            explicit FDeleteProgressTask(
                TSharedPtr<FEzProgressGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteProgressTask;

        TSharedPtr<FAsyncTask<FDeleteProgressTask>> DeleteProgress(
        );

        class EZGS2_API FModelTask :
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

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Quest::Model::FEzProgressPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzProgressGameSessionDomain> FEzProgressGameSessionDomainPtr;
}
