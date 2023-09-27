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

    class GS2INBOX_API FMessageDomain:
        public TSharedFromThis<FMessageDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> MessageName;
    private:

        FString ParentKey;

    public:

        FMessageDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> MessageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMessageDomain(
            const FMessageDomain& From
        );

        class GS2INBOX_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FMessage>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMessageDomain> Self;
            const Request::FGetMessageByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMessageDomain> Self,
                const Request::FGetMessageByUserIdRequestPtr Request
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
            Request::FGetMessageByUserIdRequestPtr Request
        );

        class GS2INBOX_API FOpenTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageDomain>,
            public TSharedFromThis<FOpenTask>
        {
            const TSharedPtr<FMessageDomain> Self;
            const Request::FOpenMessageByUserIdRequestPtr Request;
        public:
            explicit FOpenTask(
                const TSharedPtr<FMessageDomain> Self,
                const Request::FOpenMessageByUserIdRequestPtr Request
            );

            FOpenTask(
                const FOpenTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
            ) override;
        };
        friend FOpenTask;

        TSharedPtr<FAsyncTask<FOpenTask>> Open(
            Request::FOpenMessageByUserIdRequestPtr Request
        );

        class GS2INBOX_API FReadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageDomain>,
            public TSharedFromThis<FReadTask>
        {
            const TSharedPtr<FMessageDomain> Self;
            const Request::FReadMessageByUserIdRequestPtr Request;
        public:
            explicit FReadTask(
                const TSharedPtr<FMessageDomain> Self,
                const Request::FReadMessageByUserIdRequestPtr Request
            );

            FReadTask(
                const FReadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
            ) override;
        };
        friend FReadTask;

        TSharedPtr<FAsyncTask<FReadTask>> Read(
            Request::FReadMessageByUserIdRequestPtr Request
        );

        class GS2INBOX_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMessageDomain> Self;
            const Request::FDeleteMessageByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMessageDomain> Self,
                const Request::FDeleteMessageByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMessageByUserIdRequestPtr Request
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
            const TSharedPtr<FMessageDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMessageDomain> Self
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

    typedef TSharedPtr<FMessageDomain> FMessageDomainPtr;
}
