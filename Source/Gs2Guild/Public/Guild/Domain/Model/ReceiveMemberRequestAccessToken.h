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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Guild/Gs2Guild.h"
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
#include "Guild/Domain/Iterator/DescribeIgnoreUsersIterator.h"
#include "Guild/Domain/Iterator/DescribeIgnoreUsersByGuildNameIterator.h"

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
    class FGuildDomain;
    class FGuildAccessTokenDomain;
    class FJoinedGuildDomain;
    class FJoinedGuildAccessTokenDomain;
    class FLastGuildMasterActivityDomain;
    class FLastGuildMasterActivityAccessTokenDomain;
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FReceiveMemberRequestAccessTokenDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;
    class FIgnoreUserDomain;
    class FIgnoreUserAccessTokenDomain;

    class GS2GUILD_API FReceiveMemberRequestAccessTokenDomain:
        public TSharedFromThis<FReceiveMemberRequestAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GuildModelName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> GuildName() const { return AccessToken->GetUserId(); }
        TOptional<FString> FromUserId;
    private:

        FString ParentKey;

    public:

        FReceiveMemberRequestAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> FromUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FReceiveMemberRequestAccessTokenDomain(
            const FReceiveMemberRequestAccessTokenDomain& From
        );

        class GS2GUILD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FReceiveMemberRequest>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self;
            const Request::FGetReceiveRequestRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
                const Request::FGetReceiveRequestRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetReceiveRequestRequestPtr Request
        );

        class GS2GUILD_API FAcceptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self;
            const Request::FAcceptRequestRequestPtr Request;
        public:
            explicit FAcceptTask(
                const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
                const Request::FAcceptRequestRequestPtr Request
            );

            FAcceptTask(
                const FAcceptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
            Request::FAcceptRequestRequestPtr Request
        );

        class GS2GUILD_API FRejectTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>,
            public TSharedFromThis<FRejectTask>
        {
            const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self;
            const Request::FRejectRequestRequestPtr Request;
        public:
            explicit FRejectTask(
                const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
                const Request::FRejectRequestRequestPtr Request
            );

            FRejectTask(
                const FRejectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
            ) override;
        };
        friend FRejectTask;

        TSharedPtr<FAsyncTask<FRejectTask>> Reject(
            Request::FRejectRequestRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName,
            TOptional<FString> FromUserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> FromUserId
        );

        class GS2GUILD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FReceiveMemberRequest>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FReceiveMemberRequestAccessTokenDomain> FReceiveMemberRequestAccessTokenDomainPtr;
}
