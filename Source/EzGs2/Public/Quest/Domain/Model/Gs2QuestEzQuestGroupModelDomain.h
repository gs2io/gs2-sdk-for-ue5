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
#include "Quest/Domain/Model/QuestGroupModel.h"
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
#include "Gs2QuestEzQuestModelDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeQuestModelsIterator.h"
#include "Gs2QuestEzQuestGroupModelDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeQuestGroupModelsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzQuestGroupModelDomain final :
        public TSharedFromThis<FEzQuestGroupModelDomain>
    {
        Gs2::Quest::Domain::Model::FQuestGroupModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> QuestGroupName() const;

        FEzQuestGroupModelDomain(
            Gs2::Quest::Domain::Model::FQuestGroupModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Quest::Domain::Iterator::FEzDescribeQuestModelsIteratorPtr QuestModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeQuestModels(TFunction<void()> Callback);

        void UnsubscribeQuestModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Quest::Domain::Model::FEzQuestModelDomainPtr QuestModel(
            const FString QuestName
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzQuestGroupModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzQuestGroupModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzQuestGroupModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzQuestGroupModelDomain> FEzQuestGroupModelDomainPtr;
}
