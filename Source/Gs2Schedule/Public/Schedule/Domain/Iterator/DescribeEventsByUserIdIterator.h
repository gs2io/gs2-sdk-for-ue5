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

namespace Gs2::Schedule::Domain::Iterator
{

    class FDescribeEventsByUserIdIteratorLoadTask;

    class GS2SCHEDULE_API FDescribeEventsByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Schedule::Model::FEvent, FDescribeEventsByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;

        friend FDescribeEventsByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeEventsByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        TOptional<int32> FetchSize;

        FDescribeEventsByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Schedule::FGs2ScheduleRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
        );

        class GS2SCHEDULE_API IteratorImpl
        {
            friend FDescribeEventsByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeEventsByUserIdIterator::FNextTask>> Task;
            Gs2::Schedule::Model::FEventPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeEventsByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Schedule::Model::FEventPtr& operator*() const;
            Gs2::Schedule::Model::FEventPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeEventsByUserIdIterator> FDescribeEventsByUserIdIteratorPtr;

    class FDescribeEventsByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Schedule::Model::FEventPtr>>,
        public TSharedFromThis<FDescribeEventsByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeEventsByUserIdIterator> Self;

    public:
        explicit FDescribeEventsByUserIdIteratorLoadTask(
            TSharedPtr<FDescribeEventsByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Schedule::Model::FEventPtr>>> Result
        ) override;
    };
}
