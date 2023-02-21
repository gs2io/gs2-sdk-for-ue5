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

    class GS2SCHEDULE_API FEventDomain:
        public TSharedFromThis<FEventDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> EventName;
    private:

        FString ParentKey;

    public:

        FEventDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> EventName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEventDomain(
            const FEventDomain& From
        );

        class GS2SCHEDULE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FEvent>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FEventDomain> Self;
            const Request::FGetEventByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FEventDomain> Self,
                const Request::FGetEventByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetEventByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> EventName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> EventName
        );

        class GS2SCHEDULE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FEvent>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FEventDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FEventDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FEventDomain> FEventDomainPtr;
}
