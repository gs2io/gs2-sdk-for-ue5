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
#include "Gs2GuildEzGuildDomain.h"
#include "Gs2GuildEzGuildGameSessionDomain.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Model/Gs2GuildEzGuildModel.h"
#include "Guild/Model/Gs2GuildEzGuild.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Guild/Model/Gs2GuildEzSendMemberRequest.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Guild/Model/Gs2GuildEzMember.h"
#include "Guild/Model/Gs2GuildEzRoleModel.h"
#include "Gs2GuildEzSendMemberRequestGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeSendRequestsIterator.h"
#include "Gs2GuildEzJoinedGuildGameSessionDomain.h"
#include "Guild/Domain/Iterator/Gs2GuildEzDescribeJoinedGuildsIterator.h"
#include "Gs2GuildEzUserGameSessionDomain.h"
#include "Util/Configuration/GatewaySetting.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/GuildGameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FCreateGuildTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>,
            public TSharedFromThis<FCreateGuildTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString GuildModelName;
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
            explicit FCreateGuildTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString GuildModelName,
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
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>> Result
            ) override;
        };
        friend FCreateGuildTask;

        TSharedPtr<FAsyncTask<FCreateGuildTask>> CreateGuild(
            FString GuildModelName,
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

        class EZGS2_API FSendRequestTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>,
            public TSharedFromThis<FSendRequestTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString GuildModelName;
            FString TargetGuildName;

        public:
            explicit FSendRequestTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString GuildModelName,
                FString TargetGuildName
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>> Result
            ) override;
        };
        friend FSendRequestTask;

        TSharedPtr<FAsyncTask<FSendRequestTask>> SendRequest(
            FString GuildModelName,
            FString TargetGuildName
        );

        class EZGS2_API FCancelRequestTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomain>,
            public TSharedFromThis<FCancelRequestTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString GuildModelName;
            FString TargetGuildName;

        public:
            explicit FCancelRequestTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString GuildModelName,
                FString TargetGuildName
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomain>> Result
            ) override;
        };
        friend FCancelRequestTask;

        TSharedPtr<FAsyncTask<FCancelRequestTask>> CancelRequest(
            FString GuildModelName,
            FString TargetGuildName
        );

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeSendRequestsIteratorPtr SendRequests(
            const FString GuildModelName
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSendRequests(
            const FString GuildModelName,
            TFunction<void()> Callback
        );

        void UnsubscribeSendRequests(
            const FString GuildModelName,
            Gs2::Core::Domain::CallbackID CallbackId
        );

        Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomainPtr SendMemberRequest(
            const FString GuildModelName,
            const FString GuildName
        ) const;

        Gs2::UE5::Guild::Domain::Iterator::FEzDescribeJoinedGuildsIteratorPtr JoinedGuilds(
            const TOptional<FString> GuildModelName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJoinedGuilds(TFunction<void()> Callback);

        void UnsubscribeJoinedGuilds(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildGameSessionDomainPtr JoinedGuild(
            const FString GuildModelName,
            const FString GuildName
        ) const;

        class EZGS2_API FAssumeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Util::FGuildGameSession>,
            public TSharedFromThis<FAssumeTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            Gs2::UE5::Util::FGatewaySettingPtr GatewaySetting;
            FString GuildModelName;
            FString TargetGuildName;

        public:
            explicit FAssumeTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                Gs2::UE5::Util::FGatewaySettingPtr GatewaySetting,
                FString GuildModelName,
                FString TargetGuildName
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Util::FGuildGameSession>> Result
            ) override;
        };
        friend FAssumeTask;
        
        TSharedPtr<FAsyncTask<FAssumeTask>> Assume(
            Gs2::UE5::Util::FGatewaySettingPtr GatewaySetting,
            FString GuildModelName,
            FString TargetGuildName
        );
    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
