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

    class FDescribeDataObjectsByUserIdIteratorLoadTask;

    class GS2DATASTORE_API FDescribeDataObjectsByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Datastore::Model::FDataObject, FDescribeDataObjectsByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client;

        friend FDescribeDataObjectsByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeDataObjectsByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        const TOptional<FString> Status;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeDataObjectsByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Datastore::FGs2DatastoreRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> Status
        );

        class GS2DATASTORE_API IteratorImpl
        {
            friend FDescribeDataObjectsByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsByUserIdIterator::FNextTask>> Task;
            Gs2::Datastore::Model::FDataObjectPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Datastore::Model::FDataObjectPtr& operator*() const;
            Gs2::Datastore::Model::FDataObjectPtr operator->();
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
    typedef TSharedPtr<FDescribeDataObjectsByUserIdIterator> FDescribeDataObjectsByUserIdIteratorPtr;

    class FDescribeDataObjectsByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Datastore::Model::FDataObjectPtr>>,
        public TSharedFromThis<FDescribeDataObjectsByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeDataObjectsByUserIdIterator> Self;

    public:
        explicit FDescribeDataObjectsByUserIdIteratorLoadTask(
            TSharedPtr<FDescribeDataObjectsByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Datastore::Model::FDataObjectPtr>>> Result
        ) override;
    };
}
