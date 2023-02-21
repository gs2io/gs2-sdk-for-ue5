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

    class GS2INBOX_API FGlobalMessageMasterDomain:
        public TSharedFromThis<FGlobalMessageMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> GlobalMessageName;
    private:

        FString ParentKey;

    public:

        FGlobalMessageMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> GlobalMessageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGlobalMessageMasterDomain(
            const FGlobalMessageMasterDomain& From
        );

        class GS2INBOX_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FGlobalMessageMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGlobalMessageMasterDomain> Self;
            const Request::FGetGlobalMessageMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGlobalMessageMasterDomain> Self,
                const Request::FGetGlobalMessageMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGlobalMessageMasterRequestPtr Request
        );

        class GS2INBOX_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGlobalMessageMasterDomain> Self;
            const Request::FUpdateGlobalMessageMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGlobalMessageMasterDomain> Self,
                const Request::FUpdateGlobalMessageMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGlobalMessageMasterRequestPtr Request
        );

        class GS2INBOX_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FGlobalMessageMasterDomain> Self;
            const Request::FDeleteGlobalMessageMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FGlobalMessageMasterDomain> Self,
                const Request::FDeleteGlobalMessageMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FGlobalMessageMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteGlobalMessageMasterRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FGlobalMessageMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGlobalMessageMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGlobalMessageMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessageMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FGlobalMessageMasterDomain> FGlobalMessageMasterDomainPtr;
}
