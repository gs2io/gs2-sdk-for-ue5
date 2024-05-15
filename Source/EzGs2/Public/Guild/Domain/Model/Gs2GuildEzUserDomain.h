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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzSendMemberRequestDomain.h"
#include "Gs2GuildEzJoinedGuildDomain.h"
#include "Gs2GuildEzUserDomain.h"
#include "Gs2GuildEzUserDomain.h"
#include "Gs2GuildEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Guild::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Guild::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestDomainPtr SendMemberRequest(
            const FString GuildModelName,
            const FString GuildName
        ) const;

        Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildDomainPtr JoinedGuild(
            const FString GuildModelName,
            const FString GuildName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
