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
#include "Quest/Domain/Model/Namespace.h"
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
#include "Gs2QuestEzQuestGroupModelDomain.h"
#include "Quest/Domain/Iterator/Gs2QuestEzDescribeQuestGroupModelsIterator.h"
#include "Gs2QuestEzUserDomain.h"
#include "Gs2QuestEzUserDomain.h"
#include "Gs2QuestEzUserGameSessionDomain.h"
#include "Gs2QuestEzNamespaceDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Quest::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Quest::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Quest::Domain::Iterator::FEzDescribeQuestGroupModelsIteratorPtr QuestGroupModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeQuestGroupModels(TFunction<void()> Callback);

        void UnsubscribeQuestGroupModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Quest::Domain::Model::FEzQuestGroupModelDomainPtr QuestGroupModel(
            const FString QuestGroupName
        ) const;

        Gs2::UE5::Quest::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
