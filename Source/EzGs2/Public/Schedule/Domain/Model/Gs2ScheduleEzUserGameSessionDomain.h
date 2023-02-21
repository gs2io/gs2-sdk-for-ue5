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
#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"
#include "Gs2ScheduleEzTriggerGameSessionDomain.h"
#include "Schedule/Domain/Iterator/Gs2ScheduleEzDescribeTriggersIterator.h"
#include "Gs2ScheduleEzEventGameSessionDomain.h"
#include "Schedule/Domain/Iterator/Gs2ScheduleEzDescribeEventsIterator.h"
#include "Gs2ScheduleEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Schedule::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Schedule::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeTriggersIteratorPtr Triggers(
        ) const;

        Gs2::UE5::Schedule::Domain::Model::FEzTriggerGameSessionDomainPtr Trigger(
            const FString TriggerName
        ) const;

        Gs2::UE5::Schedule::Domain::Iterator::FEzDescribeEventsIteratorPtr Events(
        ) const;

        Gs2::UE5::Schedule::Domain::Model::FEzEventGameSessionDomainPtr Event(
            const FString EventName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
