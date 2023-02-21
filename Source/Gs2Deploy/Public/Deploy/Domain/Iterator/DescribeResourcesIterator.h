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
#include "Deploy/Gs2Deploy.h"

namespace Gs2::Deploy::Domain::Iterator
{

    class FDescribeResourcesIteratorLoadTask;

    class GS2DEPLOY_API FDescribeResourcesIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Deploy::Model::FResource, FDescribeResourcesIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Deploy::FGs2DeployRestClientPtr Client;

        friend FDescribeResourcesIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeResourcesIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> StackName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeResourcesIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Deploy::FGs2DeployRestClientPtr Client,
            const TOptional<FString> StackName
        );

        class GS2DEPLOY_API IteratorImpl
        {
            friend FDescribeResourcesIterator;

            TSharedPtr<FAsyncTask<Gs2::Deploy::Domain::Iterator::FDescribeResourcesIterator::FNextTask>> Task;
            Gs2::Deploy::Model::FResourcePtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Deploy::Domain::Iterator::FDescribeResourcesIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Deploy::Model::FResourcePtr& operator*() const;
            Gs2::Deploy::Model::FResourcePtr operator->();
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
    typedef TSharedPtr<FDescribeResourcesIterator> FDescribeResourcesIteratorPtr;

    class FDescribeResourcesIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Deploy::Model::FResourcePtr>>,
        public TSharedFromThis<FDescribeResourcesIteratorLoadTask>
    {
        TSharedPtr<FDescribeResourcesIterator> Self;

    public:
        explicit FDescribeResourcesIteratorLoadTask(
            TSharedPtr<FDescribeResourcesIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Deploy::Model::FResourcePtr>>> Result
        ) override;
    };
}
