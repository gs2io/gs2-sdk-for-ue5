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
#include "Inbox/Gs2Inbox.h"

namespace Gs2::Inbox::Domain::Iterator
{

    class FDescribeGlobalMessageMastersIteratorLoadTask;

    class GS2INBOX_API FDescribeGlobalMessageMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Inbox::Model::FGlobalMessageMaster, FDescribeGlobalMessageMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Inbox::FGs2InboxRestClientPtr Client;

        friend FDescribeGlobalMessageMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeGlobalMessageMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeGlobalMessageMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Inbox::FGs2InboxRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2INBOX_API IteratorImpl
        {
            friend FDescribeGlobalMessageMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Inbox::Domain::Iterator::FDescribeGlobalMessageMastersIterator::FNextTask>> Task;
            Gs2::Inbox::Model::FGlobalMessageMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Inbox::Domain::Iterator::FDescribeGlobalMessageMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Inbox::Model::FGlobalMessageMasterPtr& operator*() const;
            Gs2::Inbox::Model::FGlobalMessageMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeGlobalMessageMastersIterator> FDescribeGlobalMessageMastersIteratorPtr;

    class FDescribeGlobalMessageMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inbox::Model::FGlobalMessageMasterPtr>>,
        public TSharedFromThis<FDescribeGlobalMessageMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeGlobalMessageMastersIterator> Self;

    public:
        explicit FDescribeGlobalMessageMastersIteratorLoadTask(
            TSharedPtr<FDescribeGlobalMessageMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Inbox::Model::FGlobalMessageMasterPtr>>> Result
        ) override;
    };
}
