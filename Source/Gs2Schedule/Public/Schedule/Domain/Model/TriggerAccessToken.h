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
    class FCurrentEventMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2SCHEDULE_API FTriggerAccessTokenDomain:
        public TSharedFromThis<FTriggerAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> TriggerName;
    private:

        FString ParentKey;

    public:

        FTriggerAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> TriggerName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FTriggerAccessTokenDomain(
            const FTriggerAccessTokenDomain& From
        );

        class GS2SCHEDULE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Model::FTrigger>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FTriggerAccessTokenDomain> Self;
            const Request::FGetTriggerRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FTriggerAccessTokenDomain>& Self,
                const Request::FGetTriggerRequestPtr Request
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
            Request::FGetTriggerRequestPtr Request
        );

        class GS2SCHEDULE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FTriggerAccessTokenDomain> Self;
            const Request::FDeleteTriggerRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FTriggerAccessTokenDomain>& Self,
                const Request::FDeleteTriggerRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteTriggerRequestPtr Request
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
            const TSharedPtr<FTriggerAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FTriggerAccessTokenDomain> Self
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

    typedef TSharedPtr<FTriggerAccessTokenDomain> FTriggerAccessTokenDomainPtr;
}
