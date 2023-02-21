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
#include "MegaField/Gs2MegaField.h"

namespace Gs2::MegaField::Domain::Iterator
{

    class FDescribeNamespacesIteratorLoadTask;

    class GS2MEGAFIELD_API FDescribeNamespacesIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::MegaField::Model::FNamespace, FDescribeNamespacesIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        friend FDescribeNamespacesIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeNamespacesIteratorLoadTask>> Load() override;

public:
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeNamespacesIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::MegaField::FGs2MegaFieldRestClientPtr Client
        );

        class GS2MEGAFIELD_API IteratorImpl
        {
            friend FDescribeNamespacesIterator;

            TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeNamespacesIterator::FNextTask>> Task;
            Gs2::MegaField::Model::FNamespacePtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeNamespacesIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::MegaField::Model::FNamespacePtr& operator*() const;
            Gs2::MegaField::Model::FNamespacePtr operator->();
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
    typedef TSharedPtr<FDescribeNamespacesIterator> FDescribeNamespacesIteratorPtr;

    class FDescribeNamespacesIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::MegaField::Model::FNamespacePtr>>,
        public TSharedFromThis<FDescribeNamespacesIteratorLoadTask>
    {
        TSharedPtr<FDescribeNamespacesIterator> Self;

    public:
        explicit FDescribeNamespacesIteratorLoadTask(
            TSharedPtr<FDescribeNamespacesIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::MegaField::Model::FNamespacePtr>>> Result
        ) override;
    };
}
