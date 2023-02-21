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
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Gs2MissionEzCompleteDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzCompleteDomain final :
        public TSharedFromThis<FEzCompleteDomain>
    {
        Gs2::Mission::Domain::Model::FCompleteDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> MissionGroupName() const;

        FEzCompleteDomain(
            Gs2::Mission::Domain::Model::FCompleteDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzComplete>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCompleteDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCompleteDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Mission::Model::FEzCompletePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzCompleteDomain> FEzCompleteDomainPtr;
}
