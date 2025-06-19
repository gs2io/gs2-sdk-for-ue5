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
#include "Inbox/Gs2Inbox.h"
#include "Inbox/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Inbox/Domain/Iterator/DescribeMessagesIterator.h"
#include "Inbox/Domain/Iterator/DescribeMessagesByUserIdIterator.h"
#include "Inbox/Domain/Iterator/DescribeGlobalMessageMastersIterator.h"
#include "Inbox/Domain/Iterator/DescribeGlobalMessagesIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Inbox::Domain
{
    class FGs2InboxDomain;
    typedef TSharedPtr<FGs2InboxDomain> FGs2InboxDomainPtr;
}

namespace Gs2::Inbox::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FMessageDomain;
    class FMessageAccessTokenDomain;
    class FCurrentMessageMasterDomain;
    class FGlobalMessageMasterDomain;
    class FGlobalMessageDomain;
    class FReceivedDomain;
    class FReceivedAccessTokenDomain;

    class GS2INBOX_API FMessageAccessTokenDomain:
        public TSharedFromThis<FMessageAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inbox::Domain::FGs2InboxDomainPtr Service;
        const Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> MessageName;
    private:

        FString ParentKey;

    public:

        FMessageAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inbox::Domain::FGs2InboxDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> MessageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMessageAccessTokenDomain(
            const FMessageAccessTokenDomain& From
        );

        class GS2INBOX_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FMessage>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
            const Request::FGetMessageRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMessageAccessTokenDomain>& Self,
                const Request::FGetMessageRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMessageRequestPtr Request
        );

        class GS2INBOX_API FOpenTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>,
            public TSharedFromThis<FOpenTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
            const Request::FOpenMessageRequestPtr Request;
        public:
            explicit FOpenTask(
                const TSharedPtr<FMessageAccessTokenDomain>& Self,
                const Request::FOpenMessageRequestPtr Request
            );

            FOpenTask(
                const FOpenTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>> Result
            ) override;
        };
        friend FOpenTask;

        TSharedPtr<FAsyncTask<FOpenTask>> Open(
            Request::FOpenMessageRequestPtr Request
        );

        class GS2INBOX_API FReadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionAccessTokenDomain>,
            public TSharedFromThis<FReadTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
            const Request::FReadMessageRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FReadTask(
                const TSharedPtr<FMessageAccessTokenDomain>& Self,
                const Request::FReadMessageRequestPtr Request,
                bool SpeculativeExecute
            );

            FReadTask(
                const FReadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
            ) override;
        };
        friend FReadTask;

        TSharedPtr<FAsyncTask<FReadTask>> Read(
            Request::FReadMessageRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2INBOX_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
            const Request::FDeleteMessageRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMessageAccessTokenDomain>& Self,
                const Request::FDeleteMessageRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMessageRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> MessageName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MessageName
        );

        class GS2INBOX_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FMessage>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMessageAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inbox::Model::FMessagePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMessageAccessTokenDomain> FMessageAccessTokenDomainPtr;
}
