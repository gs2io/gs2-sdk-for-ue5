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
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzPublicProfileDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzPublicProfileDomain final :
        public TSharedFromThis<FEzPublicProfileDomain>
    {
        Gs2::Friend::Domain::Model::FPublicProfileDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzPublicProfileDomain(
            Gs2::Friend::Domain::Model::FPublicProfileDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetPublicProfileTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzPublicProfile>,
            public TSharedFromThis<FGetPublicProfileTask>
        {
            TSharedPtr<FEzPublicProfileDomain> Self;

        public:
            explicit FGetPublicProfileTask(
                TSharedPtr<FEzPublicProfileDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzPublicProfile>> Result
            ) override;
        };
        friend FGetPublicProfileTask;

        TSharedPtr<FAsyncTask<FGetPublicProfileTask>> GetPublicProfile(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzPublicProfile>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzPublicProfileDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzPublicProfileDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzPublicProfilePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzPublicProfileDomain> FEzPublicProfileDomainPtr;
}
