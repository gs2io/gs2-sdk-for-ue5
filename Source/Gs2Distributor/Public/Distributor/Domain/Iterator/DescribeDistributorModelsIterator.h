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
#include "Distributor/Gs2Distributor.h"

namespace Gs2::Distributor::Domain::Iterator
{

    class FDescribeDistributorModelsIteratorLoadTask;

    class GS2DISTRIBUTOR_API FDescribeDistributorModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Distributor::Model::FDistributorModel, FDescribeDistributorModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        friend FDescribeDistributorModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeDistributorModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeDistributorModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Distributor::FGs2DistributorRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2DISTRIBUTOR_API IteratorImpl
        {
            friend FDescribeDistributorModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator::FNextTask>> Task;
            Gs2::Distributor::Model::FDistributorModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Distributor::Model::FDistributorModelPtr& operator*() const;
            Gs2::Distributor::Model::FDistributorModelPtr operator->();
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
    typedef TSharedPtr<FDescribeDistributorModelsIterator> FDescribeDistributorModelsIteratorPtr;

    class FDescribeDistributorModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Distributor::Model::FDistributorModelPtr>>,
        public TSharedFromThis<FDescribeDistributorModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeDistributorModelsIterator> Self;

    public:
        explicit FDescribeDistributorModelsIteratorLoadTask(
            TSharedPtr<FDescribeDistributorModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Distributor::Model::FDistributorModelPtr>>> Result
        ) override;
    };
}
