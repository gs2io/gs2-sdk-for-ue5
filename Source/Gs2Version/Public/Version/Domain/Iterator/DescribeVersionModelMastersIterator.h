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

    class FDescribeVersionModelMastersIteratorLoadTask;

    class GS2VERSION_API FDescribeVersionModelMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Version::Model::FVersionModelMaster, FDescribeVersionModelMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Version::FGs2VersionRestClientPtr Client;

        friend FDescribeVersionModelMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeVersionModelMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeVersionModelMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Version::FGs2VersionRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2VERSION_API IteratorImpl
        {
            friend FDescribeVersionModelMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeVersionModelMastersIterator::FNextTask>> Task;
            Gs2::Version::Model::FVersionModelMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeVersionModelMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Version::Model::FVersionModelMasterPtr& operator*() const;
            Gs2::Version::Model::FVersionModelMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeVersionModelMastersIterator> FDescribeVersionModelMastersIteratorPtr;

    class FDescribeVersionModelMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Version::Model::FVersionModelMasterPtr>>,
        public TSharedFromThis<FDescribeVersionModelMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeVersionModelMastersIterator> Self;

    public:
        explicit FDescribeVersionModelMastersIteratorLoadTask(
            TSharedPtr<FDescribeVersionModelMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Version::Model::FVersionModelMasterPtr>>> Result
        ) override;
    };
}
