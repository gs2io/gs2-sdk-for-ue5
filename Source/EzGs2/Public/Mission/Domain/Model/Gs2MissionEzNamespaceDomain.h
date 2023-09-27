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
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Gs2MissionEzMissionGroupModelDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeMissionGroupModelsIterator.h"
#include "Gs2MissionEzCounterModelDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeCounterModelsIterator.h"
#include "Gs2MissionEzUserDomain.h"
#include "Gs2MissionEzUserDomain.h"
#include "Gs2MissionEzUserGameSessionDomain.h"
#include "Gs2MissionEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Mission::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Mission::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionGroupModelsIteratorPtr MissionGroupModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMissionGroupModels(TFunction<void()> Callback);

        void UnsubscribeMissionGroupModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Mission::Domain::Model::FEzMissionGroupModelDomainPtr MissionGroupModel(
            const FString MissionGroupName
        ) const;

        Gs2::UE5::Mission::Domain::Iterator::FEzDescribeCounterModelsIteratorPtr CounterModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCounterModels(TFunction<void()> Callback);

        void UnsubscribeCounterModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Mission::Domain::Model::FEzCounterModelDomainPtr CounterModel(
            const FString CounterName
        ) const;

        Gs2::UE5::Mission::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Mission::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
