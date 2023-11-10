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

    class GS2INBOX_API FGlobalMessageDomain:
        public TSharedFromThis<FGlobalMessageDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Inbox::Domain::FGs2InboxDomainPtr Service;
        const Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GlobalMessageName;
    private:

        FString ParentKey;

    public:

        FGlobalMessageDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Inbox::Domain::FGs2InboxDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GlobalMessageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGlobalMessageDomain(
            const FGlobalMessageDomain& From
        );

        class GS2INBOX_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FGlobalMessage>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGlobalMessageDomain> Self;
            const Request::FGetGlobalMessageRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGlobalMessageDomain>& Self,
                const Request::FGetGlobalMessageRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGlobalMessageRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> GlobalMessageName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GlobalMessageName
        );

        class GS2INBOX_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FGlobalMessage>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGlobalMessageDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGlobalMessageDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Inbox::Model::FGlobalMessagePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGlobalMessageDomain> FGlobalMessageDomainPtr;
}
