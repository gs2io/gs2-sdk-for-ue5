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
#include "Version/Gs2Version.h"

namespace Gs2::Version::Domain::Iterator
{

    class FDescribeVersionModelsIteratorLoadTask;

    class GS2VERSION_API FDescribeVersionModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Version::Model::FVersionModel, FDescribeVersionModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Version::FGs2VersionRestClientPtr Client;

        friend FDescribeVersionModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeVersionModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeVersionModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Version::FGs2VersionRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2VERSION_API IteratorImpl
        {
            friend FDescribeVersionModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeVersionModelsIterator::FNextTask>> Task;
            Gs2::Version::Model::FVersionModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeVersionModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Version::Model::FVersionModelPtr& operator*() const;
            Gs2::Version::Model::FVersionModelPtr operator->();
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
    typedef TSharedPtr<FDescribeVersionModelsIterator> FDescribeVersionModelsIteratorPtr;

    class FDescribeVersionModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Version::Model::FVersionModelPtr>>,
        public TSharedFromThis<FDescribeVersionModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeVersionModelsIterator> Self;

    public:
        explicit FDescribeVersionModelsIteratorLoadTask(
            TSharedPtr<FDescribeVersionModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Version::Model::FVersionModelPtr>>> Result
        ) override;
    };
}
