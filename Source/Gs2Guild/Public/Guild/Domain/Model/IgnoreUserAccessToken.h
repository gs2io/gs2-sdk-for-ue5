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
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FReceiveMemberRequestAccessTokenDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;
    class FIgnoreUserDomain;
    class FIgnoreUserAccessTokenDomain;

    class GS2GUILD_API FIgnoreUserAccessTokenDomain:
        public TSharedFromThis<FIgnoreUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GuildModelName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> GuildName() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FIgnoreUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FIgnoreUserAccessTokenDomain(
            const FIgnoreUserAccessTokenDomain& From
        );

        class GS2GUILD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FIgnoreUser>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FIgnoreUserAccessTokenDomain> Self;
            const Request::FGetIgnoreUserRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FIgnoreUserAccessTokenDomain>& Self,
                const Request::FGetIgnoreUserRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetIgnoreUserRequestPtr Request
        );

        class GS2GUILD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FIgnoreUserAccessTokenDomain> Self;
            const Request::FDeleteIgnoreUserRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FIgnoreUserAccessTokenDomain>& Self,
                const Request::FDeleteIgnoreUserRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteIgnoreUserRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2GUILD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FIgnoreUser>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FIgnoreUserAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FIgnoreUserAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Guild::Model::FIgnoreUserPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FIgnoreUserAccessTokenDomain> FIgnoreUserAccessTokenDomainPtr;
}
