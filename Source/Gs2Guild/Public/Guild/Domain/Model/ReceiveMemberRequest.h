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

    class GS2GUILD_API FReceiveMemberRequestDomain:
        public TSharedFromThis<FReceiveMemberRequestDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Guild::Domain::FGs2GuildDomainPtr Service;
        const Gs2::Guild::FGs2GuildRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GuildModelName;
        TOptional<FString> GuildName;
        TOptional<FString> FromUserId;
    private:

        FString ParentKey;

    public:

        FReceiveMemberRequestDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Guild::Domain::FGs2GuildDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GuildModelName,
            const TOptional<FString> GuildName,
            const TOptional<FString> FromUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FReceiveMemberRequestDomain(
            const FReceiveMemberRequestDomain& From
        );

        class GS2GUILD_API FGetReceiveRequestByGuildNameTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>,
            public TSharedFromThis<FGetReceiveRequestByGuildNameTask>
        {
            const TSharedPtr<FReceiveMemberRequestDomain> Self;
            const Request::FGetReceiveRequestByGuildNameRequestPtr Request;
        public:
            explicit FGetReceiveRequestByGuildNameTask(
                const TSharedPtr<FReceiveMemberRequestDomain>& Self,
                const Request::FGetReceiveRequestByGuildNameRequestPtr Request
            );

            FGetReceiveRequestByGuildNameTask(
                const FGetReceiveRequestByGuildNameTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain>> Result
            ) override;
        };
        friend FGetReceiveRequestByGuildNameTask;

        TSharedPtr<FAsyncTask<FGetReceiveRequestByGuildNameTask>> GetReceiveRequestByGuildName(
            Request::FGetReceiveRequestByGuildNameRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GuildModelName,
            TOptional<FString> GuildName,
            TOptional<FString> TargetGuildName,
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
            const TSharedPtr<FReceiveMemberRequestDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FReceiveMemberRequestDomain> Self
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

    typedef TSharedPtr<FReceiveMemberRequestDomain> FReceiveMemberRequestDomainPtr;
}
