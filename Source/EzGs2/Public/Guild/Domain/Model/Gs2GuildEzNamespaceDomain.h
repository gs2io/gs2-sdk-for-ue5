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
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzGuildModelDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeGuildModelsIterator.h"
#include "Gs2GuildEzUserDomain.h"
#include "Gs2GuildEzUserDomain.h"
#include "Gs2GuildEzUserGameSessionDomain.h"
#include "Gs2GuildEzGuildDomain.h"
#include "Gs2GuildEzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Guild::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Guild::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeGuildModelsIteratorPtr GuildModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGuildModels(TFunction<void()> Callback);

        void UnsubscribeGuildModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Guild::Domain::Model::FEzGuildModelDomainPtr GuildModel(
            const FString GuildModelName
        ) const;

        Gs2::UE5::Guild::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Guild::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::FGameSessionPtr GameSession
        ) const;

        Gs2::UE5::Guild::Domain::Model::FEzGuildDomainPtr Guild(
            const FString GuildModelName,
            const FString GuildName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
