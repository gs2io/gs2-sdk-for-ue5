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

    class GS2INBOX_API FCurrentMessageMasterDomain:
        public TSharedFromThis<FCurrentMessageMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Inbox::FGs2InboxRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentMessageMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentMessageMasterDomain(
            const FCurrentMessageMasterDomain& From
        );

        class GS2INBOX_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentMessageMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentMessageMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2INBOX_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FCurrentMessageMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentMessageMasterDomain> Self;
            const Request::FGetCurrentMessageMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentMessageMasterDomain> Self,
                const Request::FGetCurrentMessageMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FCurrentMessageMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentMessageMasterRequestPtr Request
        );

        class GS2INBOX_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentMessageMasterDomain> Self;
            const Request::FUpdateCurrentMessageMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentMessageMasterDomain> Self,
                const Request::FUpdateCurrentMessageMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentMessageMasterRequestPtr Request
        );

        class GS2INBOX_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentMessageMasterDomain> Self;
            const Request::FUpdateCurrentMessageMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentMessageMasterDomain> Self,
                const Request::FUpdateCurrentMessageMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FCurrentMessageMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentMessageMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2INBOX_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Inbox::Model::FCurrentMessageMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentMessageMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentMessageMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FCurrentMessageMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentMessageMasterDomain> FCurrentMessageMasterDomainPtr;
}
