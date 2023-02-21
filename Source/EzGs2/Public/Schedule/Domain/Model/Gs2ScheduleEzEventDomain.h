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
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"
#include "Gs2ScheduleEzEventDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    class EZGS2_API FEzEventDomain final :
        public TSharedFromThis<FEzEventDomain>
    {
        Gs2::Schedule::Domain::Model::FEventDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> EventName() const;

        FEzEventDomain(
            Gs2::Schedule::Domain::Model::FEventDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzEvent>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzEventDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzEventDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Schedule::Model::FEzEventPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzEventDomain> FEzEventDomainPtr;
}
