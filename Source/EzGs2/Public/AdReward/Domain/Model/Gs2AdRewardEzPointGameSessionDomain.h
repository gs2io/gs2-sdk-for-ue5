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
#include "AdReward/Domain/Model/PointAccessToken.h"
#include "AdReward/Model/Gs2AdRewardEzPoint.h"
#include "Gs2AdRewardEzPointGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::AdReward::Domain::Model
{

    class EZGS2_API FEzPointGameSessionDomain final :
        public TSharedFromThis<FEzPointGameSessionDomain>
    {
        Gs2::AdReward::Domain::Model::FPointAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzPointGameSessionDomain(
            Gs2::AdReward::Domain::Model::FPointAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::AdReward::Model::FEzPoint>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPointGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPointGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::AdReward::Model::FEzPointPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::AdReward::Model::FEzPointPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzPointGameSessionDomain> FEzPointGameSessionDomainPtr;
}
