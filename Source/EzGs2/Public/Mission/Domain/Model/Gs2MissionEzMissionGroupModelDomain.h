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
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzConsumeAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzTargetCounterModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Gs2MissionEzMissionTaskModelDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeMissionTaskModelsIterator.h"
#include "Gs2MissionEzMissionGroupModelDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeMissionGroupModelsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzMissionGroupModelDomain final :
        public TSharedFromThis<FEzMissionGroupModelDomain>
    {
        Gs2::Mission::Domain::Model::FMissionGroupModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> MissionGroupName() const;

        FEzMissionGroupModelDomain(
            Gs2::Mission::Domain::Model::FMissionGroupModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionTaskModelsIteratorPtr MissionTaskModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMissionTaskModels(TFunction<void()> Callback);

        void UnsubscribeMissionTaskModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Mission::Domain::Model::FEzMissionTaskModelDomainPtr MissionTaskModel(
            const FString MissionTaskName
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzMissionGroupModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzMissionGroupModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzMissionGroupModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzMissionGroupModelDomain> FEzMissionGroupModelDomainPtr;
}
