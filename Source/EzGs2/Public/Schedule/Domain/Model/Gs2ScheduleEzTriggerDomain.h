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
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"
#include "Schedule/Model/Gs2ScheduleEzRepeatSchedule.h"
#include "Gs2ScheduleEzTriggerDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    class EZGS2_API FEzTriggerDomain final :
        public TSharedFromThis<FEzTriggerDomain>
    {
        Gs2::Schedule::Domain::Model::FTriggerDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> TriggerName() const;

        FEzTriggerDomain(
            Gs2::Schedule::Domain::Model::FTriggerDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzTrigger>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzTriggerDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzTriggerDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Schedule::Model::FEzTriggerPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Schedule::Model::FEzTriggerPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzTriggerDomain> FEzTriggerDomainPtr;
}
