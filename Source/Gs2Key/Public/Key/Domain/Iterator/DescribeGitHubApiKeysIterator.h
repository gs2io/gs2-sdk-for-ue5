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
#include "Key/Gs2Key.h"

namespace Gs2::Key::Domain::Iterator
{

    class FDescribeGitHubApiKeysIteratorLoadTask;

    class GS2KEY_API FDescribeGitHubApiKeysIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Key::Model::FGitHubApiKey, FDescribeGitHubApiKeysIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Key::FGs2KeyRestClientPtr Client;

        friend FDescribeGitHubApiKeysIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeGitHubApiKeysIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeGitHubApiKeysIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Key::FGs2KeyRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2KEY_API IteratorImpl
        {
            friend FDescribeGitHubApiKeysIterator;

            TSharedPtr<FAsyncTask<Gs2::Key::Domain::Iterator::FDescribeGitHubApiKeysIterator::FNextTask>> Task;
            Gs2::Key::Model::FGitHubApiKeyPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Key::Domain::Iterator::FDescribeGitHubApiKeysIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Key::Model::FGitHubApiKeyPtr& operator*() const;
            Gs2::Key::Model::FGitHubApiKeyPtr operator->();
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
    typedef TSharedPtr<FDescribeGitHubApiKeysIterator> FDescribeGitHubApiKeysIteratorPtr;

    class FDescribeGitHubApiKeysIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Key::Model::FGitHubApiKeyPtr>>,
        public TSharedFromThis<FDescribeGitHubApiKeysIteratorLoadTask>
    {
        TSharedPtr<FDescribeGitHubApiKeysIterator> Self;

    public:
        explicit FDescribeGitHubApiKeysIteratorLoadTask(
            TSharedPtr<FDescribeGitHubApiKeysIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Key::Model::FGitHubApiKeyPtr>>> Result
        ) override;
    };
}
