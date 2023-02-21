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
#include "Schedule/Gs2Schedule.h"
#include "Schedule/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventMastersIterator.h"
#include "Schedule/Domain/Iterator/DescribeTriggersIterator.h"
#include "Schedule/Domain/Iterator/DescribeTriggersByUserIdIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventsIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventsByUserIdIterator.h"

namespace Gs2::Schedule::Domain::Model
{
    class FNamespaceDomain;
    class FEventMasterDomain;
    class FTriggerDomain;
    class FTriggerAccessTokenDomain;
    class FEventDomain;
    class FEventAccessTokenDomain;
    class FCurrentEventMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2SCHEDULE_API FCurrentEventMasterDomain:
        public TSharedFromThis<FCurrentEventMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentEventMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentEventMasterDomain(
            const FCurrentEventMasterDomain& From
        );

        class GS2SCHEDULE_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentEventMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentEventMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2SCHEDULE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FCurrentEventMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentEventMasterDomain> Self;
            const Request::FGetCurrentEventMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentEventMasterDomain> Self,
                const Request::FGetCurrentEventMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FCurrentEventMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentEventMasterRequestPtr Request
        );

        class GS2SCHEDULE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentEventMasterDomain> Self;
            const Request::FUpdateCurrentEventMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentEventMasterDomain> Self,
                const Request::FUpdateCurrentEventMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentEventMasterRequestPtr Request
        );

        class GS2SCHEDULE_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentEventMasterDomain> Self;
            const Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentEventMasterDomain> Self,
                const Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SCHEDULE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FCurrentEventMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentEventMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentEventMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FCurrentEventMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentEventMasterDomain> FCurrentEventMasterDomainPtr;
}
