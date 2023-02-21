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
#include "Quest/Gs2Quest.h"

namespace Gs2::Quest::Domain::Iterator
{

    class FDescribeCompletedQuestListsIteratorLoadTask;

    class GS2QUEST_API FDescribeCompletedQuestListsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Quest::Model::FCompletedQuestList, FDescribeCompletedQuestListsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        friend FDescribeCompletedQuestListsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeCompletedQuestListsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeCompletedQuestListsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Quest::FGs2QuestRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2QUEST_API IteratorImpl
        {
            friend FDescribeCompletedQuestListsIterator;

            TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator::FNextTask>> Task;
            Gs2::Quest::Model::FCompletedQuestListPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Quest::Model::FCompletedQuestListPtr& operator*() const;
            Gs2::Quest::Model::FCompletedQuestListPtr operator->();
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
    typedef TSharedPtr<FDescribeCompletedQuestListsIterator> FDescribeCompletedQuestListsIteratorPtr;

    class FDescribeCompletedQuestListsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Quest::Model::FCompletedQuestListPtr>>,
        public TSharedFromThis<FDescribeCompletedQuestListsIteratorLoadTask>
    {
        TSharedPtr<FDescribeCompletedQuestListsIterator> Self;

    public:
        explicit FDescribeCompletedQuestListsIteratorLoadTask(
            TSharedPtr<FDescribeCompletedQuestListsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FCompletedQuestListPtr>>> Result
        ) override;
    };
}
