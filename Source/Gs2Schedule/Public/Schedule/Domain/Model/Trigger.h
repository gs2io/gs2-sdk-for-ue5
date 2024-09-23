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

    class GS2SCHEDULE_API FTriggerDomain:
        public TSharedFromThis<FTriggerDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> TriggerName;
    private:

        FString ParentKey;

    public:

        FTriggerDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> TriggerName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FTriggerDomain(
            const FTriggerDomain& From
        );

        class GS2SCHEDULE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FTrigger>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FTriggerDomain> Self;
            const Request::FGetTriggerByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FTriggerDomain>& Self,
                const Request::FGetTriggerByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetTriggerByUserIdRequestPtr Request
        );

        class GS2SCHEDULE_API FTriggerTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FTriggerDomain>,
            public TSharedFromThis<FTriggerTask>
        {
            const TSharedPtr<FTriggerDomain> Self;
            const Request::FTriggerByUserIdRequestPtr Request;
        public:
            explicit FTriggerTask(
                const TSharedPtr<FTriggerDomain>& Self,
                const Request::FTriggerByUserIdRequestPtr Request
            );

            FTriggerTask(
                const FTriggerTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
            ) override;
        };
        friend FTriggerTask;

        TSharedPtr<FAsyncTask<FTriggerTask>> Trigger(
            Request::FTriggerByUserIdRequestPtr Request
        );

        class GS2SCHEDULE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FTriggerDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FTriggerDomain> Self;
            const Request::FDeleteTriggerByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FTriggerDomain>& Self,
                const Request::FDeleteTriggerByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteTriggerByUserIdRequestPtr Request
        );

        class GS2SCHEDULE_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FTriggerDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FTriggerDomain> Self;
            const Request::FVerifyTriggerByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FTriggerDomain>& Self,
                const Request::FVerifyTriggerByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyTriggerByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> TriggerName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TriggerName
        );

        class GS2SCHEDULE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FTrigger>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FTriggerDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FTriggerDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FTrigger>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Schedule::Model::FTriggerPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FTriggerDomain> FTriggerDomainPtr;
}
