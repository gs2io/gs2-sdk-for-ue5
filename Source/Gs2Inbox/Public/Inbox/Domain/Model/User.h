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

    class GS2INBOX_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inbox::Domain::FGs2InboxDomainPtr Service;
        const Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inbox::Domain::FGs2InboxDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2INBOX_API FSendMessageTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FMessageDomain>,
            public TSharedFromThis<FSendMessageTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FSendMessageByUserIdRequestPtr Request;
        public:
            explicit FSendMessageTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FSendMessageByUserIdRequestPtr Request
            );

            FSendMessageTask(
                const FSendMessageTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
            ) override;
        };
        friend FSendMessageTask;

        TSharedPtr<FAsyncTask<FSendMessageTask>> SendMessage(
            Request::FSendMessageByUserIdRequestPtr Request
        );

        class GS2INBOX_API FReceiveGlobalMessageTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>,
            public TSharedFromThis<FReceiveGlobalMessageTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FReceiveGlobalMessageByUserIdRequestPtr Request;
        public:
            explicit FReceiveGlobalMessageTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FReceiveGlobalMessageByUserIdRequestPtr Request
            );

            FReceiveGlobalMessageTask(
                const FReceiveGlobalMessageTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>> Result
            ) override;
        };
        friend FReceiveGlobalMessageTask;

        TSharedPtr<FAsyncTask<FReceiveGlobalMessageTask>> ReceiveGlobalMessage(
            Request::FReceiveGlobalMessageByUserIdRequestPtr Request
        );

        class GS2INBOX_API FBatchReadMessagesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FBatchReadMessagesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FBatchReadMessagesByUserIdRequestPtr Request;
        public:
            explicit FBatchReadMessagesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FBatchReadMessagesByUserIdRequestPtr Request
            );

            FBatchReadMessagesTask(
                const FBatchReadMessagesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FBatchReadMessagesTask;

        TSharedPtr<FAsyncTask<FBatchReadMessagesTask>> BatchReadMessages(
            Request::FBatchReadMessagesByUserIdRequestPtr Request
        );

        Gs2::Inbox::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr Messages(
            const TOptional<bool> IsRead = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMessages(
            TFunction<void()> Callback
        );

        void UnsubscribeMessages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain> Message(
            const FString MessageName
        );

        TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain> Received(
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

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
