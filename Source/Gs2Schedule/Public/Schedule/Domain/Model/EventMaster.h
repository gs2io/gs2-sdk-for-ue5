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
#include "Schedule/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventMastersIterator.h"
#include "Schedule/Domain/Iterator/DescribeTriggersIterator.h"
#include "Schedule/Domain/Iterator/DescribeTriggersByUserIdIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventsIterator.h"
#include "Schedule/Domain/Iterator/DescribeEventsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Schedule::Domain
{
    class FGs2ScheduleDomain;
    typedef TSharedPtr<FGs2ScheduleDomain> FGs2ScheduleDomainPtr;
}

namespace Gs2::Schedule::Domain::Model
{
    class FNamespaceDomain;
    class FEventMasterDomain;
    class FTriggerDomain;
    class FTriggerAccessTokenDomain;
    class FEventDomain;
    class FEventAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FCurrentEventMasterDomain;

    class GS2SCHEDULE_API FEventMasterDomain:
        public TSharedFromThis<FEventMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> EventName;
    private:

        FString ParentKey;

    public:

        FEventMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> EventName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEventMasterDomain(
            const FEventMasterDomain& From
        );

        class GS2SCHEDULE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FEventMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FEventMasterDomain> Self;
            const Request::FGetEventMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FEventMasterDomain>& Self,
                const Request::FGetEventMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEventMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetEventMasterRequestPtr Request
        );

        class GS2SCHEDULE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FEventMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FEventMasterDomain> Self;
            const Request::FUpdateEventMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FEventMasterDomain>& Self,
                const Request::FUpdateEventMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateEventMasterRequestPtr Request
        );

        class GS2SCHEDULE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FEventMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FEventMasterDomain> Self;
            const Request::FDeleteEventMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FEventMasterDomain>& Self,
                const Request::FDeleteEventMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteEventMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> EventName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> EventName
        );

        class GS2SCHEDULE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FEventMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FEventMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FEventMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEventMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Schedule::Model::FEventMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FEventMasterDomain> FEventMasterDomainPtr;
}
