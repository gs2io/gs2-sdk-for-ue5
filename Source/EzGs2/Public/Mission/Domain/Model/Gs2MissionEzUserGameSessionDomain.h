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
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzConsumeAction.h"
#include "Mission/Model/Gs2MissionEzVerifyAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzTargetCounterModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Mission/Model/Gs2MissionEzVerifyActionResult.h"
#include "Mission/Model/Gs2MissionEzConsumeActionResult.h"
#include "Mission/Model/Gs2MissionEzAcquireActionResult.h"
#include "Mission/Model/Gs2MissionEzTransactionResult.h"
#include "Gs2MissionEzCompleteGameSessionDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeCompletesIterator.h"
#include "Gs2MissionEzCounterGameSessionDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeCountersIterator.h"
#include "Gs2MissionEzUserGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Mission::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzComplete>>> ChangedCompletes() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Mission::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Mission::Domain::Iterator::FEzDescribeCompletesIteratorPtr Completes(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCompletes(TFunction<void()> Callback);

        void UnsubscribeCompletes(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomainPtr Complete(
            const FString MissionGroupName
        ) const;

        Gs2::UE5::Mission::Domain::Iterator::FEzDescribeCountersIteratorPtr Counters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCounters(TFunction<void()> Callback);

        void UnsubscribeCounters(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Mission::Domain::Model::FEzCounterGameSessionDomainPtr Counter(
            const FString CounterName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
