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
#include "Guild/Domain/Model/GuildAccessToken.h"
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
#include "Gs2GuildEzReceiveMemberRequestGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeReceiveRequestsIterator.h"
#include "Gs2GuildEzIgnoreUserGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeIgnoreUsersIterator.h"
#include "Gs2GuildEzLastGuildMasterActivityGameSessionDomain.h"
#include "Gs2GuildEzGuildGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzSearchGuildsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzGuildGameSessionDomain final :
        public TSharedFromThis<FEzGuildGameSessionDomain>
    {
        Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> GuildModelName() const;
        TOptional<FString> GuildName() const;

        FEzGuildGameSessionDomain(
            Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FUpdateGuildTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FUpdateGuildTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString DisplayName;
            FString JoinPolicy;
            TOptional<int32> Attribute1;
            TOptional<int32> Attribute2;
            TOptional<int32> Attribute3;
            TOptional<int32> Attribute4;
            TOptional<int32> Attribute5;
            TOptional<FString> Metadata;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles;
            TOptional<FString> GuildMemberDefaultRole;

        public:
            explicit FUpdateGuildTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString DisplayName,
                FString JoinPolicy,
                TOptional<int32> Attribute1 = TOptional<int32>(),
                TOptional<int32> Attribute2 = TOptional<int32>(),
                TOptional<int32> Attribute3 = TOptional<int32>(),
                TOptional<int32> Attribute4 = TOptional<int32>(),
                TOptional<int32> Attribute5 = TOptional<int32>(),
                TOptional<FString> Metadata = TOptional<FString>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>>(),
                TOptional<FString> GuildMemberDefaultRole = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateGuildTask;

        TSharedPtr<FAsyncTask<FUpdateGuildTask>> UpdateGuild(
            FString DisplayName,
            FString JoinPolicy,
            TOptional<int32> Attribute1 = TOptional<int32>(),
            TOptional<int32> Attribute2 = TOptional<int32>(),
            TOptional<int32> Attribute3 = TOptional<int32>(),
            TOptional<int32> Attribute4 = TOptional<int32>(),
            TOptional<int32> Attribute5 = TOptional<int32>(),
            TOptional<FString> Metadata = TOptional<FString>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>>(),
            TOptional<FString> GuildMemberDefaultRole = TOptional<FString>()
        );

        class EZGS2_API FDeleteMemberFromGuildTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FDeleteMemberFromGuildTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FDeleteMemberFromGuildTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteMemberFromGuildTask;

        TSharedPtr<FAsyncTask<FDeleteMemberFromGuildTask>> DeleteMemberFromGuild(
            FString TargetUserId
        );

        class EZGS2_API FUpdateGuildMemberRoleTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FUpdateGuildMemberRoleTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString TargetUserId;
            FString RoleName;

        public:
            explicit FUpdateGuildMemberRoleTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString TargetUserId,
                FString RoleName
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateGuildMemberRoleTask;

        TSharedPtr<FAsyncTask<FUpdateGuildMemberRoleTask>> UpdateGuildMemberRole(
            FString TargetUserId,
            FString RoleName
        );

        class EZGS2_API FDeleteGuildTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>,
            public TSharedFromThis<FDeleteGuildTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;

        public:
            explicit FDeleteGuildTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteGuildTask;

        TSharedPtr<FAsyncTask<FDeleteGuildTask>> DeleteGuild(
        );

        class EZGS2_API FAddIgnoreUserTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>,
            public TSharedFromThis<FAddIgnoreUserTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;
            FString UserId;

        public:
            explicit FAddIgnoreUserTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self,
                FString UserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>> Result
            ) override;
        };
        friend FAddIgnoreUserTask;

        TSharedPtr<FAsyncTask<FAddIgnoreUserTask>> AddIgnoreUser(
            FString UserId
        );

        class EZGS2_API FPromoteSeniorMemberTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomain>,
            public TSharedFromThis<FPromoteSeniorMemberTask>
        {
            TSharedPtr<FEzGuildGameSessionDomain> Self;

        public:
            explicit FPromoteSeniorMemberTask(
                TSharedPtr<FEzGuildGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomain>> Result
            ) override;
        };
        friend FPromoteSeniorMemberTask;

        TSharedPtr<FAsyncTask<FPromoteSeniorMemberTask>> PromoteSeniorMember(
        );

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveRequestsIteratorPtr ReceiveRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveRequests(TFunction<void()> Callback);

        void UnsubscribeReceiveRequests(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomainPtr ReceiveMemberRequest(
            const FString FromUserId
        ) const;

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeIgnoreUsersIteratorPtr IgnoreUsers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeIgnoreUsers(TFunction<void()> Callback);

        void UnsubscribeIgnoreUsers(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomainPtr IgnoreUser(
        ) const;

        Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomainPtr LastGuildMasterActivity(
        ) const;

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
