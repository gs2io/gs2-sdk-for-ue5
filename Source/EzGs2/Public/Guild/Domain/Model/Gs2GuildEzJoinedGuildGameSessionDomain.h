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
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzJoinedGuildGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeJoinedGuildsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzJoinedGuildGameSessionDomain final :
        public TSharedFromThis<FEzJoinedGuildGameSessionDomain>
    {
        Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> GuildModelName() const;
        TOptional<FString> GuildName() const;

        FEzJoinedGuildGameSessionDomain(
            Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Model::FEzJoinedGuild>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzJoinedGuildGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzJoinedGuildGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Guild::Model::FEzJoinedGuildPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzJoinedGuildPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzJoinedGuildGameSessionDomain> FEzJoinedGuildGameSessionDomainPtr;
}
