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

    class GS2SCHEDULE_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        public:
        TOptional<bool> InSchedule;
        TOptional<int64> ScheduleStartAt;
        TOptional<int64> ScheduleEndAt;
        TOptional<bool> IsGlobalSchedule;
        TOptional<FString> NextPageToken;
        TOptional<bool> GetInSchedule() const
        {
            return InSchedule;
        }
        TOptional<int64> GetScheduleStartAt() const
        {
            return ScheduleStartAt;
        }
        TOptional<int64> GetScheduleEndAt() const
        {
            return ScheduleEndAt;
        }
        TOptional<bool> GetIsGlobalSchedule() const
        {
            return IsGlobalSchedule;
        }
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
            const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Schedule::Domain::Iterator::FDescribeTriggersByUserIdIteratorPtr Triggers(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTriggers(
            TFunction<void()> Callback

        );

        class FCollectTriggersTask;

        Gs2::Core::Domain::CallbackID SubscribeTriggers(
            TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateTriggers(const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2SCHEDULE_API FSubscribeTriggersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeTriggersWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback;
        const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeTriggersWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken);
            FSubscribeTriggersWithInitialCallTask(const FSubscribeTriggersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeTriggersWithInitialCallTask>> SubscribeTriggersWithInitialCall(
            TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        void UnsubscribeTriggers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain> Trigger(
            const FString TriggerName
        );

        Gs2::Schedule::Domain::Iterator::FDescribeEventsByUserIdIteratorPtr Events(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEvents(
            TFunction<void()> Callback

        );

        class FCollectEventsTask;

        Gs2::Core::Domain::CallbackID SubscribeEvents(
            TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateEvents(const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2SCHEDULE_API FSubscribeEventsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeEventsWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback;
        const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeEventsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken);
            FSubscribeEventsWithInitialCallTask(const FSubscribeEventsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeEventsWithInitialCallTask>> SubscribeEventsWithInitialCall(
            TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        void UnsubscribeEvents(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Schedule::Domain::Model::FEventDomain> Event(
            const FString EventName
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
