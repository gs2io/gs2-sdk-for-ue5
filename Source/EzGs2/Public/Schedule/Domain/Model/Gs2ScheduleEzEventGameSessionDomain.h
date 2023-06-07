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
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"
#include "Gs2ScheduleEzEventGameSessionDomain.h"
#include "Schedule/Domain/Iterator/Gs2ScheduleEzDescribeEventsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    class EZGS2_API FEzEventGameSessionDomain final :
        public TSharedFromThis<FEzEventGameSessionDomain>
    {
        Gs2::Schedule::Domain::Model::FEventAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<int32> RepeatCount() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> EventName() const;

        FEzEventGameSessionDomain(
            Gs2::Schedule::Domain::Model::FEventAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetEventTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzEvent>,
            public TSharedFromThis<FGetEventTask>
        {
            TSharedPtr<FEzEventGameSessionDomain> Self;

        public:
            explicit FGetEventTask(
                TSharedPtr<FEzEventGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Schedule::Model::FEzEvent>> Result
            ) override;
        };
        friend FGetEventTask;

        TSharedPtr<FAsyncTask<FGetEventTask>> GetEvent(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzEvent>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzEventGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzEventGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Schedule::Model::FEzEventPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzEventGameSessionDomain> FEzEventGameSessionDomainPtr;
}
