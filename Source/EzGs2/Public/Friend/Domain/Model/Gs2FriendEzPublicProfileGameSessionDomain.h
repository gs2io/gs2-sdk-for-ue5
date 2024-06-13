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
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzPublicProfileGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzPublicProfileGameSessionDomain final :
        public TSharedFromThis<FEzPublicProfileGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzPublicProfileGameSessionDomain(
            Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzPublicProfile>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPublicProfileGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPublicProfileGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzPublicProfilePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzPublicProfilePtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzPublicProfileGameSessionDomain> FEzPublicProfileGameSessionDomainPtr;
}
