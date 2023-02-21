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
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Model/Gs2QuestEzContents.h"
#include "Quest/Model/Gs2QuestEzConsumeAction.h"
#include "Quest/Model/Gs2QuestEzAcquireAction.h"
#include "Quest/Model/Gs2QuestEzReward.h"
#include "Quest/Model/Gs2QuestEzConfig.h"
#include "Quest/Model/Gs2QuestEzProgress.h"
#include "Quest/Model/Gs2QuestEzCompletedQuestList.h"
#include "Quest/Model/Gs2QuestEzQuestGroupModel.h"
#include "Quest/Model/Gs2QuestEzQuestModel.h"
#include "Gs2QuestEzCompletedQuestListGameSessionDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeCompletedQuestListsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzCompletedQuestListGameSessionDomain final :
        public TSharedFromThis<FEzCompletedQuestListGameSessionDomain>
    {
        Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> QuestGroupName() const;

        FEzCompletedQuestListGameSessionDomain(
            Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetCompletedQuestListTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzCompletedQuestList>,
            public TSharedFromThis<FGetCompletedQuestListTask>
        {
            TSharedPtr<FEzCompletedQuestListGameSessionDomain> Self;

        public:
            explicit FGetCompletedQuestListTask(
                TSharedPtr<FEzCompletedQuestListGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzCompletedQuestList>> Result
            ) override;
        };
        friend FGetCompletedQuestListTask;

        TSharedPtr<FAsyncTask<FGetCompletedQuestListTask>> GetCompletedQuestList(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzCompletedQuestList>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCompletedQuestListGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCompletedQuestListGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzCompletedQuestListGameSessionDomain> FEzCompletedQuestListGameSessionDomainPtr;
}
