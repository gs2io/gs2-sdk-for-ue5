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
#include "SerialKey/Gs2SerialKey.h"

namespace Gs2::SerialKey::Domain::Iterator
{

    class FDescribeIssueJobsIteratorLoadTask;

    class GS2SERIALKEY_API FDescribeIssueJobsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::SerialKey::Model::FIssueJob, FDescribeIssueJobsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;

        friend FDescribeIssueJobsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeIssueJobsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> CampaignModelName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeIssueJobsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CampaignModelName
        );

        class GS2SERIALKEY_API IteratorImpl
        {
            friend FDescribeIssueJobsIterator;

            TSharedPtr<FAsyncTask<Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIterator::FNextTask>> Task;
            Gs2::SerialKey::Model::FIssueJobPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::SerialKey::Model::FIssueJobPtr& operator*() const;
            Gs2::SerialKey::Model::FIssueJobPtr operator->();
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
    typedef TSharedPtr<FDescribeIssueJobsIterator> FDescribeIssueJobsIteratorPtr;

    class FDescribeIssueJobsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::SerialKey::Model::FIssueJobPtr>>,
        public TSharedFromThis<FDescribeIssueJobsIteratorLoadTask>
    {
        TSharedPtr<FDescribeIssueJobsIterator> Self;

    public:
        explicit FDescribeIssueJobsIteratorLoadTask(
            TSharedPtr<FDescribeIssueJobsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::SerialKey::Model::FIssueJobPtr>>> Result
        ) override;
    };
}
