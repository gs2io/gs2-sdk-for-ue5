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
#include "Exchange/Gs2Exchange.h"

namespace Gs2::Exchange::Domain::Iterator
{

    class FDescribeRateModelsIteratorLoadTask;

    class GS2EXCHANGE_API FDescribeRateModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Exchange::Model::FRateModel, FDescribeRateModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        friend FDescribeRateModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeRateModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeRateModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Exchange::FGs2ExchangeRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2EXCHANGE_API IteratorImpl
        {
            friend FDescribeRateModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator::FNextTask>> Task;
            Gs2::Exchange::Model::FRateModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Exchange::Model::FRateModelPtr& operator*() const;
            Gs2::Exchange::Model::FRateModelPtr operator->();
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
    typedef TSharedPtr<FDescribeRateModelsIterator> FDescribeRateModelsIteratorPtr;

    class FDescribeRateModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Exchange::Model::FRateModelPtr>>,
        public TSharedFromThis<FDescribeRateModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeRateModelsIterator> Self;

    public:
        explicit FDescribeRateModelsIteratorLoadTask(
            TSharedPtr<FDescribeRateModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Exchange::Model::FRateModelPtr>>> Result
        ) override;
    };
}
