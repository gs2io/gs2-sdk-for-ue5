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
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzProfileGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzProfileGameSessionDomain final :
        public TSharedFromThis<FEzProfileGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FProfileAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzProfileGameSessionDomain(
            Gs2::Friend::Domain::Model::FProfileAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetProfileTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzProfile>,
            public TSharedFromThis<FGetProfileTask>
        {
            TSharedPtr<FEzProfileGameSessionDomain> Self;

        public:
            explicit FGetProfileTask(
                TSharedPtr<FEzProfileGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzProfile>> Result
            ) override;
        };
        friend FGetProfileTask;

        TSharedPtr<FAsyncTask<FGetProfileTask>> GetProfile(
        );

        class FUpdateProfileTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomain>,
            public TSharedFromThis<FUpdateProfileTask>
        {
            TSharedPtr<FEzProfileGameSessionDomain> Self;
            TOptional<FString> PublicProfile;
            TOptional<FString> FollowerProfile;
            TOptional<FString> FriendProfile;

        public:
            explicit FUpdateProfileTask(
                TSharedPtr<FEzProfileGameSessionDomain> Self,
                TOptional<FString> PublicProfile = TOptional<FString>(),
                TOptional<FString> FollowerProfile = TOptional<FString>(),
                TOptional<FString> FriendProfile = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateProfileTask;

        TSharedPtr<FAsyncTask<FUpdateProfileTask>> UpdateProfile(
            TOptional<FString> PublicProfile = TOptional<FString>(),
            TOptional<FString> FollowerProfile = TOptional<FString>(),
            TOptional<FString> FriendProfile = TOptional<FString>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzProfile>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzProfileGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzProfileGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzProfilePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzProfileGameSessionDomain> FEzProfileGameSessionDomainPtr;
}
