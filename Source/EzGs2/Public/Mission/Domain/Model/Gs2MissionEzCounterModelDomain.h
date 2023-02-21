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
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Gs2MissionEzCounterModelDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeCounterModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzCounterModelDomain final :
        public TSharedFromThis<FEzCounterModelDomain>
    {
        Gs2::Mission::Domain::Model::FCounterModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> CounterName() const;

        FEzCounterModelDomain(
            Gs2::Mission::Domain::Model::FCounterModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetCounterModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzCounterModel>,
            public TSharedFromThis<FGetCounterModelTask>
        {
            TSharedPtr<FEzCounterModelDomain> Self;

        public:
            explicit FGetCounterModelTask(
                TSharedPtr<FEzCounterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModel>> Result
            ) override;
        };
        friend FGetCounterModelTask;

        TSharedPtr<FAsyncTask<FGetCounterModelTask>> GetCounterModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzCounterModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCounterModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCounterModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzCounterModelDomain> FEzCounterModelDomainPtr;
}
