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

    class FDescribeQuestModelsIteratorLoadTask;

    class GS2QUEST_API FDescribeQuestModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Quest::Model::FQuestModel, FDescribeQuestModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        friend FDescribeQuestModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeQuestModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> QuestGroupName;
        TOptional<int32> FetchSize;

        FDescribeQuestModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Quest::FGs2QuestRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> QuestGroupName
        );

        class GS2QUEST_API IteratorImpl
        {
            friend FDescribeQuestModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator::FNextTask>> Task;
            Gs2::Quest::Model::FQuestModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Quest::Model::FQuestModelPtr& operator*() const;
            Gs2::Quest::Model::FQuestModelPtr operator->();
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
    typedef TSharedPtr<FDescribeQuestModelsIterator> FDescribeQuestModelsIteratorPtr;

    class FDescribeQuestModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Quest::Model::FQuestModelPtr>>,
        public TSharedFromThis<FDescribeQuestModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeQuestModelsIterator> Self;

    public:
        explicit FDescribeQuestModelsIteratorLoadTask(
            TSharedPtr<FDescribeQuestModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FQuestModelPtr>>> Result
        ) override;
    };
}
