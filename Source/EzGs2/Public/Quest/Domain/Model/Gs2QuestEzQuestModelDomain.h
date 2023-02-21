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
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Model/Gs2QuestEzContents.h"
#include "Quest/Model/Gs2QuestEzConsumeAction.h"
#include "Quest/Model/Gs2QuestEzAcquireAction.h"
#include "Quest/Model/Gs2QuestEzReward.h"
#include "Quest/Model/Gs2QuestEzConfig.h"
#include "Quest/Model/Gs2QuestEzProgress.h"
#include "Quest/Model/Gs2QuestEzCompletedQuestList.h"
#include "Quest/Model/Gs2QuestEzQuestGroupModel.h"
#include "Quest/Model/Gs2QuestEzQuestModel.h"
#include "Gs2QuestEzQuestModelDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeQuestModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzQuestModelDomain final :
        public TSharedFromThis<FEzQuestModelDomain>
    {
        Gs2::Quest::Domain::Model::FQuestModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> QuestGroupName() const;
        TOptional<FString> QuestName() const;

        FEzQuestModelDomain(
            Gs2::Quest::Domain::Model::FQuestModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetQuestTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzQuestModel>,
            public TSharedFromThis<FGetQuestTask>
        {
            TSharedPtr<FEzQuestModelDomain> Self;

        public:
            explicit FGetQuestTask(
                TSharedPtr<FEzQuestModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>> Result
            ) override;
        };
        friend FGetQuestTask;

        TSharedPtr<FAsyncTask<FGetQuestTask>> GetQuest(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzQuestModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzQuestModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzQuestModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzQuestModelDomain> FEzQuestModelDomainPtr;
}
