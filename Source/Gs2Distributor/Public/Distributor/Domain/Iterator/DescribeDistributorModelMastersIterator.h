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

    class FDescribeDistributorModelMastersIteratorLoadTask;

    class GS2DISTRIBUTOR_API FDescribeDistributorModelMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Distributor::Model::FDistributorModelMaster, FDescribeDistributorModelMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        friend FDescribeDistributorModelMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeDistributorModelMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeDistributorModelMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Distributor::FGs2DistributorRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2DISTRIBUTOR_API IteratorImpl
        {
            friend FDescribeDistributorModelMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIterator::FNextTask>> Task;
            Gs2::Distributor::Model::FDistributorModelMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Distributor::Model::FDistributorModelMasterPtr& operator*() const;
            Gs2::Distributor::Model::FDistributorModelMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeDistributorModelMastersIterator> FDescribeDistributorModelMastersIteratorPtr;

    class FDescribeDistributorModelMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>>,
        public TSharedFromThis<FDescribeDistributorModelMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeDistributorModelMastersIterator> Self;

    public:
        explicit FDescribeDistributorModelMastersIteratorLoadTask(
            TSharedPtr<FDescribeDistributorModelMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>>> Result
        ) override;
    };
}
