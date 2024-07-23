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
    class FUserAccessTokenDomain;
    class FGuildDomain;
    class FJoinedGuildDomain;
    class FJoinedGuildAccessTokenDomain;
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;
    class FIgnoreUserDomain;

    class GS2GUILD_API FJoinedGuildDomain:
        public TSharedFromThis<FJoinedGuildDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> GuildModelName;
        TOptional<FString> GuildName;
    private:

        FString ParentKey;

    public:

        FJoinedGuildDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> GuildModelName,
            const TOptional<FString> GuildName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FJoinedGuildDomain(
            const FJoinedGuildDomain& From
        );

        class GS2GUILD_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FJoinedGuild>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FJoinedGuildDomain> Self;
            const Request::FGetJoinedGuildByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FJoinedGuildDomain>& Self,
                const Request::FGetJoinedGuildByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FJoinedGuild>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetJoinedGuildByUserIdRequestPtr Request
        );

        class GS2GUILD_API FWithdrawalTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FJoinedGuildDomain>,
            public TSharedFromThis<FWithdrawalTask>
        {
            const TSharedPtr<FJoinedGuildDomain> Self;
            const Request::FWithdrawalByUserIdRequestPtr Request;
        public:
            explicit FWithdrawalTask(
                const TSharedPtr<FJoinedGuildDomain>& Self,
                const Request::FWithdrawalByUserIdRequestPtr Request
            );

            FWithdrawalTask(
                const FWithdrawalTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildDomain>> Result
            ) override;
        };
        friend FWithdrawalTask;

        TSharedPtr<FAsyncTask<FWithdrawalTask>> Withdrawal(
            Request::FWithdrawalByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName
        );

        class GS2GUILD_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Model::FJoinedGuild>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FJoinedGuildDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FJoinedGuildDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Model::FJoinedGuild>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Guild::Model::FJoinedGuildPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FJoinedGuildDomain> FJoinedGuildDomainPtr;
}
