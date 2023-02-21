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
#include "Realtime/Gs2Realtime.h"

namespace Gs2::Realtime::Domain::Iterator
{

    class FDescribeRoomsIteratorLoadTask;

    class GS2REALTIME_API FDescribeRoomsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Realtime::Model::FRoom, FDescribeRoomsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Realtime::FGs2RealtimeRestClientPtr Client;

        friend FDescribeRoomsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeRoomsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeRoomsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Realtime::FGs2RealtimeRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2REALTIME_API IteratorImpl
        {
            friend FDescribeRoomsIterator;

            TSharedPtr<FAsyncTask<Gs2::Realtime::Domain::Iterator::FDescribeRoomsIterator::FNextTask>> Task;
            Gs2::Realtime::Model::FRoomPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Realtime::Domain::Iterator::FDescribeRoomsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Realtime::Model::FRoomPtr& operator*() const;
            Gs2::Realtime::Model::FRoomPtr operator->();
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
    typedef TSharedPtr<FDescribeRoomsIterator> FDescribeRoomsIteratorPtr;

    class FDescribeRoomsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Realtime::Model::FRoomPtr>>,
        public TSharedFromThis<FDescribeRoomsIteratorLoadTask>
    {
        TSharedPtr<FDescribeRoomsIterator> Self;

    public:
        explicit FDescribeRoomsIteratorLoadTask(
            TSharedPtr<FDescribeRoomsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Realtime::Model::FRoomPtr>>> Result
        ) override;
    };
}
