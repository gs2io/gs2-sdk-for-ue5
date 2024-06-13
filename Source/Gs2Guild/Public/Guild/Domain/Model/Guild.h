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
#include "Guild/Domain/Iterator/SearchGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsIterator.h"
#include "Guild/Domain/Iterator/SearchGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsIterator.h"
#include "Guild/Domain/Iterator/DescribeJoinedGuildsByUserIdIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeReceiveRequestsByGuildNameIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsIterator.h"
#include "Guild/Domain/Iterator/DescribeSendRequestsByUserIdIterator.h"

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
    class FGuildDomain;
    class FJoinedGuildDomain;
    class FJoinedGuildAccessTokenDomain;
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;

    class GS2GUILD_API FGuildDomain:
        public TSharedFromThis<FGuildDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GuildModelName;
        TOptional<FString> GuildName;
    private:

        FString ParentKey;

    public:

        FGuildDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const TOptional<FString> GuildName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGuildDomain(
            const FGuildDomain& From
        );

        class GS2GUILD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FGuild>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FGetGuildRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGuildDomain>& Self,
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

        class GS2GUILD_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FUpdateGuildByGuildNameRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FUpdateGuildByGuildNameRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGuildByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FDeleteMemberTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FDeleteMemberTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FDeleteMemberByGuildNameRequestPtr Request;
        public:
            explicit FDeleteMemberTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FDeleteMemberByGuildNameRequestPtr Request
            );

            FDeleteMemberTask(
                const FDeleteMemberTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FDeleteMemberTask;

        TSharedPtr<FAsyncTask<FDeleteMemberTask>> DeleteMember(
            Request::FDeleteMemberByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FUpdateMemberRoleTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FUpdateMemberRoleTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FUpdateMemberRoleByGuildNameRequestPtr Request;
        public:
            explicit FUpdateMemberRoleTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FUpdateMemberRoleByGuildNameRequestPtr Request
            );

            FUpdateMemberRoleTask(
                const FUpdateMemberRoleTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FUpdateMemberRoleTask;

        TSharedPtr<FAsyncTask<FUpdateMemberRoleTask>> UpdateMemberRole(
            Request::FUpdateMemberRoleByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FDeleteGuildByGuildNameRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FDeleteGuildByGuildNameRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteGuildByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FIncreaseMaximumCurrentMaximumMemberCountTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FIncreaseMaximumCurrentMaximumMemberCountTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request;
        public:
            explicit FIncreaseMaximumCurrentMaximumMemberCountTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
            );

            FIncreaseMaximumCurrentMaximumMemberCountTask(
                const FIncreaseMaximumCurrentMaximumMemberCountTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FIncreaseMaximumCurrentMaximumMemberCountTask;

        TSharedPtr<FAsyncTask<FIncreaseMaximumCurrentMaximumMemberCountTask>> IncreaseMaximumCurrentMaximumMemberCount(
            Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FDecreaseMaximumCurrentMaximumMemberCountTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FDecreaseMaximumCurrentMaximumMemberCountTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request;
        public:
            explicit FDecreaseMaximumCurrentMaximumMemberCountTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
            );

            FDecreaseMaximumCurrentMaximumMemberCountTask(
                const FDecreaseMaximumCurrentMaximumMemberCountTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FDecreaseMaximumCurrentMaximumMemberCountTask;

        TSharedPtr<FAsyncTask<FDecreaseMaximumCurrentMaximumMemberCountTask>> DecreaseMaximumCurrentMaximumMemberCount(
            Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FSetMaximumCurrentMaximumMemberCountTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FSetMaximumCurrentMaximumMemberCountTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request;
        public:
            explicit FSetMaximumCurrentMaximumMemberCountTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
            );

            FSetMaximumCurrentMaximumMemberCountTask(
                const FSetMaximumCurrentMaximumMemberCountTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FSetMaximumCurrentMaximumMemberCountTask;

        TSharedPtr<FAsyncTask<FSetMaximumCurrentMaximumMemberCountTask>> SetMaximumCurrentMaximumMemberCount(
            Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FAcceptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FAcceptRequestByGuildNameRequestPtr Request;
        public:
            explicit FAcceptTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FAcceptRequestByGuildNameRequestPtr Request
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
            Request::FAcceptRequestByGuildNameRequestPtr Request
        );

        class GS2GUILD_API FRejectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>,
            public TSharedFromThis<FRejectTask>
        {
            const TSharedPtr<FGuildDomain> Self;
            const Request::FRejectRequestByGuildNameRequestPtr Request;
        public:
            explicit FRejectTask(
                const TSharedPtr<FGuildDomain>& Self,
                const Request::FRejectRequestByGuildNameRequestPtr Request
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
            Request::FRejectRequestByGuildNameRequestPtr Request
        );

        Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsByGuildNameIteratorPtr ReceiveRequestsByGuildName(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveRequestsByGuildName(
            TFunction<void()> Callback
        );

        void UnsubscribeReceiveRequestsByGuildName(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain> ReceiveMemberRequest(
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
            const TSharedPtr<FGuildDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr accessToken;
        public:
            explicit FModelTask(
                const TSharedPtr<FGuildDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr accessToken
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model(Gs2::Auth::Model::FAccessTokenPtr accessToken);

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Guild::Model::FGuildPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGuildDomain> FGuildDomainPtr;
}
