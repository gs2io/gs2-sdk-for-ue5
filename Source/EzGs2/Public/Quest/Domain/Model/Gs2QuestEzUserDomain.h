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
#include "Quest/Domain/Model/User.h"
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
#include "Gs2QuestEzCompletedQuestListDomain.h"
#include "Gs2QuestEzProgressDomain.h"
#include "Gs2QuestEzUserDomain.h"
#include "Gs2QuestEzUserDomain.h"
#include "Gs2QuestEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Quest::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Quest::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Quest::Domain::Model::FEzCompletedQuestListDomainPtr CompletedQuestList(
            const FString QuestGroupName
        ) const;

        Gs2::UE5::Quest::Domain::Model::FEzProgressDomainPtr Progress(
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
