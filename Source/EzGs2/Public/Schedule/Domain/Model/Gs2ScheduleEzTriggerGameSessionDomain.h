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
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"
#include "Schedule/Model/Gs2ScheduleEzRepeatSchedule.h"
#include "Gs2ScheduleEzTriggerGameSessionDomain.h"
#include "Schedule/Domain/Iterator/Gs2ScheduleEzDescribeTriggersIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    class EZGS2_API FEzTriggerGameSessionDomain final :
        public TSharedFromThis<FEzTriggerGameSessionDomain>
    {
        Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> TriggerName() const;

        FEzTriggerGameSessionDomain(
            Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetTriggerTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzTrigger>,
            public TSharedFromThis<FGetTriggerTask>
        {
            TSharedPtr<FEzTriggerGameSessionDomain> Self;

        public:
            explicit FGetTriggerTask(
                TSharedPtr<FEzTriggerGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Schedule::Model::FEzTrigger>> Result
            ) override;
        };
        friend FGetTriggerTask;

        TSharedPtr<FAsyncTask<FGetTriggerTask>> GetTrigger(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzTrigger>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzTriggerGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzTriggerGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Schedule::Model::FEzTriggerPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzTriggerGameSessionDomain> FEzTriggerGameSessionDomainPtr;
}
