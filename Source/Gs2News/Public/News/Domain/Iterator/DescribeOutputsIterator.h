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
#include "News/Gs2News.h"

namespace Gs2::News::Domain::Iterator
{

    class FDescribeOutputsIteratorLoadTask;

    class GS2NEWS_API FDescribeOutputsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::News::Model::FOutput, FDescribeOutputsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::News::FGs2NewsRestClientPtr Client;

        friend FDescribeOutputsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeOutputsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UploadToken;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeOutputsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::News::FGs2NewsRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UploadToken
        );

        class GS2NEWS_API IteratorImpl
        {
            friend FDescribeOutputsIterator;

            TSharedPtr<FAsyncTask<Gs2::News::Domain::Iterator::FDescribeOutputsIterator::FNextTask>> Task;
            Gs2::News::Model::FOutputPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::News::Domain::Iterator::FDescribeOutputsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::News::Model::FOutputPtr& operator*() const;
            Gs2::News::Model::FOutputPtr operator->();
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
    typedef TSharedPtr<FDescribeOutputsIterator> FDescribeOutputsIteratorPtr;

    class FDescribeOutputsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::News::Model::FOutputPtr>>,
        public TSharedFromThis<FDescribeOutputsIteratorLoadTask>
    {
        TSharedPtr<FDescribeOutputsIterator> Self;

    public:
        explicit FDescribeOutputsIteratorLoadTask(
            TSharedPtr<FDescribeOutputsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::News::Model::FOutputPtr>>> Result
        ) override;
    };
}
