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
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzIgnoreUser.h"
#include "Guild/Model/Gs2GuildEzLastGuildMasterActivity.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Guild/Model/Gs2GuildEzVerifyActionResult.h"
#include "Guild/Model/Gs2GuildEzConsumeActionResult.h"
#include "Guild/Model/Gs2GuildEzAcquireActionResult.h"
#include "Guild/Model/Gs2GuildEzTransactionResult.h"
#include "Gs2GuildEzJoinedGuildDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzJoinedGuildDomain final :
        public TSharedFromThis<FEzJoinedGuildDomain>
    {
        Gs2::Guild::Domain::Model::FJoinedGuildDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> GuildModelName() const;
        TOptional<FString> GuildName() const;

        FEzJoinedGuildDomain(
            Gs2::Guild::Domain::Model::FJoinedGuildDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Model::FEzJoinedGuild>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzJoinedGuildDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzJoinedGuildDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Guild::Model::FEzJoinedGuildPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzJoinedGuildPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzJoinedGuildDomain> FEzJoinedGuildDomainPtr;
}
