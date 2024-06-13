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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Guild/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Guild/Domain/Iterator/DescribeGuildModelMastersIterator.h"
#include "Guild/Domain/Iterator/DescribeGuildModelsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Guild::Domain
{
    class FGs2GuildDomain;
    typedef TSharedPtr<FGs2GuildDomain> FGs2GuildDomainPtr;
}

namespace Gs2::Guild::Domain::Model
{
    class FNamespaceDomain;
    class FGuildModelMasterDomain;
    class FGuildModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FGuildAccessTokenDomain;
    class FJoinedGuildDomain;
    class FJoinedGuildAccessTokenDomain;
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FReceiveMemberRequestAccessTokenDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;

    class GS2GUILD_API FGuildAccessTokenDomain:
        public TSharedFromThis<FGuildAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GuildModelName;
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> GuildName() const
        {
            return AccessToken->GetUserId();
        }
    private:

        FString ParentKey;

    public:

        FGuildAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGuildAccessTokenDomain(
            const FGuildAccessTokenDomain& From
        );

        class GS2GUILD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FGuild>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FGetGuildRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FGetGuildRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGuildRequestPtr Request
        );

        class GS2GUILD_API FUpdateByNameTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>,
            public TSharedFromThis<FUpdateByNameTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FUpdateGuildByGuildNameRequestPtr Request;
        public:
            explicit FUpdateByNameTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FUpdateGuildByGuildNameRequestPtr Request
            );

            FUpdateByNameTask(
                const FUpdateByNameTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateByNameTask;
        
        class GS2GUILD_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FUpdateGuildRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FUpdateGuildRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGuildRequestPtr Request
        );

        class GS2GUILD_API FDeleteMemberTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>,
            public TSharedFromThis<FDeleteMemberTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FDeleteMemberRequestPtr Request;
        public:
            explicit FDeleteMemberTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FDeleteMemberRequestPtr Request
            );

            FDeleteMemberTask(
                const FDeleteMemberTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteMemberTask;

        TSharedPtr<FAsyncTask<FDeleteMemberTask>> DeleteMember(
            Request::FDeleteMemberRequestPtr Request
        );

        class GS2GUILD_API FUpdateMemberRoleTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>,
            public TSharedFromThis<FUpdateMemberRoleTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FUpdateMemberRoleRequestPtr Request;
        public:
            explicit FUpdateMemberRoleTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FUpdateMemberRoleRequestPtr Request
            );

            FUpdateMemberRoleTask(
                const FUpdateMemberRoleTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateMemberRoleTask;

        TSharedPtr<FAsyncTask<FUpdateMemberRoleTask>> UpdateMemberRole(
            Request::FUpdateMemberRoleRequestPtr Request
        );

        class GS2GUILD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FDeleteGuildRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FDeleteGuildRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteGuildRequestPtr Request
        );

        class GS2GUILD_API FAcceptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FAcceptRequestRequestPtr Request;
        public:
            explicit FAcceptTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FAcceptRequestRequestPtr Request
            );

            FAcceptTask(
                const FAcceptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
            Request::FAcceptRequestRequestPtr Request
        );

        class GS2GUILD_API FRejectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>,
            public TSharedFromThis<FRejectTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
            const Request::FRejectRequestRequestPtr Request;
        public:
            explicit FRejectTask(
                const TSharedPtr<FGuildAccessTokenDomain>& Self,
                const Request::FRejectRequestRequestPtr Request
            );

            FRejectTask(
                const FRejectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
            ) override;
        };
        friend FRejectTask;

        TSharedPtr<FAsyncTask<FRejectTask>> Reject(
            Request::FRejectRequestRequestPtr Request
        );

        Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr ReceiveRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveRequests(
            TFunction<void()> Callback
        );

        void UnsubscribeReceiveRequests(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain> ReceiveMemberRequest(
            const FString FromUserId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName
        );

        class GS2GUILD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FGuild>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGuildAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGuildAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Guild::Model::FGuildPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGuildAccessTokenDomain> FGuildAccessTokenDomainPtr;
}
