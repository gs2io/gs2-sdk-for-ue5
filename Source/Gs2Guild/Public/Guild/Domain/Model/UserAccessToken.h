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
#include "Guild/Gs2Guild.h"
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
#include "Guild/Domain/Iterator/DescribeReceiveRequestsByGuildNameIterator.h"
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
    class FGuildDomain;
    class FJoinedGuildDomain;
    class FJoinedGuildAccessTokenDomain;
    class FCurrentGuildMasterDomain;
    class FReceiveMemberRequestDomain;
    class FSendMemberRequestDomain;
    class FSendMemberRequestAccessTokenDomain;

    class GS2GUILD_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2GUILD_API FCreateGuildTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FCreateGuildTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FCreateGuildRequestPtr Request;
        public:
            explicit FCreateGuildTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FCreateGuildRequestPtr Request
            );

            FCreateGuildTask(
                const FCreateGuildTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FCreateGuildTask;

        TSharedPtr<FAsyncTask<FCreateGuildTask>> CreateGuild(
            Request::FCreateGuildRequestPtr Request
        );

        class GS2GUILD_API FAssumeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Domain::Model::FAccessTokenDomain>,
            public TSharedFromThis<FAssumeTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FAssumeRequestPtr Request;
        public:
            explicit FAssumeTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FAssumeRequestPtr Request
            );

            FAssumeTask(
                const FAssumeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
            ) override;
        };
        friend FAssumeTask;

        TSharedPtr<FAsyncTask<FAssumeTask>> Assume(
            Request::FAssumeRequestPtr Request
        );

        class GS2GUILD_API FSendRequestTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FGuildDomain>,
            public TSharedFromThis<FSendRequestTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FSendRequestRequestPtr Request;
        public:
            explicit FSendRequestTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FSendRequestRequestPtr Request
            );

            FSendRequestTask(
                const FSendRequestTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
            ) override;
        };
        friend FSendRequestTask;

        TSharedPtr<FAsyncTask<FSendRequestTask>> SendRequest(
            Request::FSendRequestRequestPtr Request
        );

        class GS2GUILD_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FDeleteRequestRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FDeleteRequestRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRequestRequestPtr Request
        );

        Gs2::Guild::Domain::Iterator::FDescribeSendRequestsIteratorPtr SendRequests(
            const FString GuildModelName
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSendRequests(
            const FString GuildModelName,
            TFunction<void()> Callback
        );

        void UnsubscribeSendRequests(
            const FString GuildModelName,
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain> SendMemberRequest(
            const FString GuildModelName,
            const FString GuildName
        );

        Gs2::Guild::Domain::Iterator::FSearchGuildsIteratorPtr SearchGuilds(
            const FString GuildModelName,
            const TOptional<FString> DisplayName = TOptional<FString>(),
            const TSharedPtr<TArray<int32>> Attributes1 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes2 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes3 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes4 = nullptr,
            const TSharedPtr<TArray<int32>> Attributes5 = nullptr,
            const TSharedPtr<TArray<FString>> JoinPolicies = nullptr,
            const TOptional<bool> IncludeFullMembersGuild = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIteratorPtr JoinedGuilds(
            const TOptional<FString> GuildModelName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJoinedGuilds(
            TFunction<void()> Callback
        );

        void UnsubscribeJoinedGuilds(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain> JoinedGuild(
            const FString GuildModelName,
            const FString GuildName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
