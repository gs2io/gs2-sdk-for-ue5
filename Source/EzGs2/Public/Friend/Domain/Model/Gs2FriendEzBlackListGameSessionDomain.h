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
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzBlackListGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeBlackListIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzBlackListGameSessionDomain final :
        public TSharedFromThis<FEzBlackListGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FBlackListAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzBlackListGameSessionDomain(
            Gs2::Friend::Domain::Model::FBlackListAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FRegisterBlackListTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>,
            public TSharedFromThis<FRegisterBlackListTask>
        {
            TSharedPtr<FEzBlackListGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FRegisterBlackListTask(
                TSharedPtr<FEzBlackListGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>> Result
            ) override;
        };
        friend FRegisterBlackListTask;

        TSharedPtr<FAsyncTask<FRegisterBlackListTask>> RegisterBlackList(
            FString TargetUserId
        );

        class FUnregisterBlackListTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>,
            public TSharedFromThis<FUnregisterBlackListTask>
        {
            TSharedPtr<FEzBlackListGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FUnregisterBlackListTask(
                TSharedPtr<FEzBlackListGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>> Result
            ) override;
        };
        friend FUnregisterBlackListTask;

        TSharedPtr<FAsyncTask<FUnregisterBlackListTask>> UnregisterBlackList(
            FString TargetUserId
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzBlackList>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBlackListGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBlackListGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzBlackListPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzBlackListGameSessionDomain> FEzBlackListGameSessionDomainPtr;
}
