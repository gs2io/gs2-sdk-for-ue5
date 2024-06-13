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
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzReceiveMemberRequestDomain.h"
#include "Gs2GuildEzGuildDomain.h"
#include "Gs2GuildEzReceiveMemberRequestGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeReceiveMemberRequestsIterator.h"
#include "Guild/Domain/Model/GuildAccessToken.h"
#include "Util/Net/GuildGameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzGuildGameSessionDomain final :
        public TSharedFromThis<FEzGuildGameSessionDomain>
    {
        Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGuildGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> GuildModelName() const;
        TOptional<FString> GuildName() const;

        FEzGuildGameSessionDomain(
            Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGuildGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomainPtr ReceiveMemberRequest(
            const FString FromUserId
        ) const;

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveMemberRequestsIteratorPtr ReceiveMemberRequests(
        ) const;
        
        class EZGS2_API FUpdateTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString DisplayName;
            FString JoinPolicy;
            TOptional<int32> Attribute1;
            TOptional<int32> Attribute2;
            TOptional<int32> Attribute3;
            TOptional<int32> Attribute4;
            TOptional<int32> Attribute5;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles;
            TOptional<FString> GuildMemberDefaultRole;

        public:
            explicit FUpdateTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString DisplayName,
                FString JoinPolicy,
                TOptional<int32> Attribute1 = TOptional<int32>(),
                TOptional<int32> Attribute2 = TOptional<int32>(),
                TOptional<int32> Attribute3 = TOptional<int32>(),
                TOptional<int32> Attribute4 = TOptional<int32>(),
                TOptional<int32> Attribute5 = TOptional<int32>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>>(),
                TOptional<FString> GuildMemberDefaultRole = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            FString DisplayName,
            FString JoinPolicy,
            TOptional<int32> Attribute1 = TOptional<int32>(),
            TOptional<int32> Attribute2 = TOptional<int32>(),
            TOptional<int32> Attribute3 = TOptional<int32>(),
            TOptional<int32> Attribute4 = TOptional<int32>(),
            TOptional<int32> Attribute5 = TOptional<int32>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>>(),
            TOptional<FString> GuildMemberDefaultRole = TOptional<FString>()
        );
        
        class EZGS2_API FDeleteMemberTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FDeleteMemberTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FDeleteMemberTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteMemberTask;

        TSharedPtr<FAsyncTask<FDeleteMemberTask>> DeleteMember(
            FString TargetUserId
        );
        
        class EZGS2_API FUpdateMemberRoleTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FUpdateMemberRoleTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString TargetUserId;
            FString RoleName;

        public:
            explicit FUpdateMemberRoleTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString TargetUserId,
                FString RoleName
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateMemberRoleTask;
        
        TSharedPtr<FAsyncTask<FUpdateMemberRoleTask>> UpdateMemberRole(
            FString TargetUserId,
            FString RoleName
        );

        class EZGS2_API FDeleteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FDeleteMemberTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString TargetUserId;
            FString RoleName;

        public:
            explicit FDeleteTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTask;
        
        TSharedPtr<FAsyncTask<FDeleteTask>> Delete();
        
        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Model::FEzGuild>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Guild::Model::FEzGuildPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzGuildPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzGuildGameSessionDomain> FEzGuildGameSessionDomainPtr;
}
