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
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
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
#include "Gs2GuildEzLastGuildMasterActivityDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzLastGuildMasterActivityDomain final :
        public TSharedFromThis<FEzLastGuildMasterActivityDomain>
    {
        Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> GuildModelName() const;
        TOptional<FString> GuildName() const;

        FEzLastGuildMasterActivityDomain(
            Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Model::FEzLastGuildMasterActivity>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzLastGuildMasterActivityDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzLastGuildMasterActivityDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Guild::Model::FEzLastGuildMasterActivityPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzLastGuildMasterActivityPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzLastGuildMasterActivityDomain> FEzLastGuildMasterActivityDomainPtr;
}
