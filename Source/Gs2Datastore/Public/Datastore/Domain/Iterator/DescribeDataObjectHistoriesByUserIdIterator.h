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
#include "Datastore/Gs2Datastore.h"

namespace Gs2::Datastore::Domain::Iterator
{

    class FDescribeDataObjectHistoriesByUserIdIteratorLoadTask;

    class GS2DATASTORE_API FDescribeDataObjectHistoriesByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Datastore::Model::FDataObjectHistory, FDescribeDataObjectHistoriesByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client;

        friend FDescribeDataObjectHistoriesByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeDataObjectHistoriesByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        const TOptional<FString> DataObjectName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeDataObjectHistoriesByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Datastore::FGs2DatastoreRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> DataObjectName
        );

        class GS2DATASTORE_API IteratorImpl
        {
            friend FDescribeDataObjectHistoriesByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIterator::FNextTask>> Task;
            Gs2::Datastore::Model::FDataObjectHistoryPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Datastore::Model::FDataObjectHistoryPtr& operator*() const;
            Gs2::Datastore::Model::FDataObjectHistoryPtr operator->();
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
    typedef TSharedPtr<FDescribeDataObjectHistoriesByUserIdIterator> FDescribeDataObjectHistoriesByUserIdIteratorPtr;

    class FDescribeDataObjectHistoriesByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>>,
        public TSharedFromThis<FDescribeDataObjectHistoriesByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeDataObjectHistoriesByUserIdIterator> Self;

    public:
        explicit FDescribeDataObjectHistoriesByUserIdIteratorLoadTask(
            TSharedPtr<FDescribeDataObjectHistoriesByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>>> Result
        ) override;
    };
}
