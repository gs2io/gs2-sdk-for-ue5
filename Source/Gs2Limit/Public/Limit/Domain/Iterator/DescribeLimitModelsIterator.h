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
#include "Limit/Gs2Limit.h"

namespace Gs2::Limit::Domain::Iterator
{

    class FDescribeLimitModelsIteratorLoadTask;

    class GS2LIMIT_API FDescribeLimitModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Limit::Model::FLimitModel, FDescribeLimitModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Limit::FGs2LimitRestClientPtr Client;

        friend FDescribeLimitModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeLimitModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeLimitModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Limit::FGs2LimitRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2LIMIT_API IteratorImpl
        {
            friend FDescribeLimitModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FNextTask>> Task;
            Gs2::Limit::Model::FLimitModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Limit::Model::FLimitModelPtr& operator*() const;
            Gs2::Limit::Model::FLimitModelPtr operator->();
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
    typedef TSharedPtr<FDescribeLimitModelsIterator> FDescribeLimitModelsIteratorPtr;

    class FDescribeLimitModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Limit::Model::FLimitModelPtr>>,
        public TSharedFromThis<FDescribeLimitModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeLimitModelsIterator> Self;

    public:
        explicit FDescribeLimitModelsIteratorLoadTask(
            TSharedPtr<FDescribeLimitModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Limit::Model::FLimitModelPtr>>> Result
        ) override;
    };
}
