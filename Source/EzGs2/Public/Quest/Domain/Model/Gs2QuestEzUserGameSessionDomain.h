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
#include "Quest/Domain/Model/UserAccessToken.h"
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
#include "Gs2QuestEzCompletedQuestListGameSessionDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeCompletedQuestListsIterator.h"
#include "Gs2QuestEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Quest::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Quest::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FStartTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>,
            public TSharedFromThis<FStartTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString QuestGroupName;
            FString QuestName;
            TOptional<bool> Force;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config;

        public:
            explicit FStartTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString QuestGroupName,
                FString QuestName,
                TOptional<bool> Force = TOptional<bool>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>> Result
            ) override;
        };
        friend FStartTask;

        TSharedPtr<FAsyncTask<FStartTask>> Start(
            FString QuestGroupName,
            FString QuestName,
            TOptional<bool> Force = TOptional<bool>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
        );

        class FEndTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>,
            public TSharedFromThis<FEndTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            bool IsComplete;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config;

        public:
            explicit FEndTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                bool IsComplete,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            bool IsComplete,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>>()
        );

        class FDeleteProgressTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>,
            public TSharedFromThis<FDeleteProgressTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;

        public:
            explicit FDeleteProgressTask(
                TSharedPtr<FEzUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteProgressTask;

        TSharedPtr<FAsyncTask<FDeleteProgressTask>> DeleteProgress(
        );

        Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomainPtr Progress(
        ) const;

        Gs2::UE5::Quest::Domain::Iterator::FEzDescribeCompletedQuestListsIteratorPtr CompletedQuestLists(
        ) const;

        Gs2::UE5::Quest::Domain::Model::FEzCompletedQuestListGameSessionDomainPtr CompletedQuestList(
            const FString QuestGroupName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
