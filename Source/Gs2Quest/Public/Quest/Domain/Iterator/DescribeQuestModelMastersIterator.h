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

    class FDescribeQuestModelMastersIteratorLoadTask;

    class GS2QUEST_API FDescribeQuestModelMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Quest::Model::FQuestModelMaster, FDescribeQuestModelMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        friend FDescribeQuestModelMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeQuestModelMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> QuestGroupName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeQuestModelMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Quest::FGs2QuestRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> QuestGroupName
        );

        class GS2QUEST_API IteratorImpl
        {
            friend FDescribeQuestModelMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIterator::FNextTask>> Task;
            Gs2::Quest::Model::FQuestModelMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Quest::Model::FQuestModelMasterPtr& operator*() const;
            Gs2::Quest::Model::FQuestModelMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeQuestModelMastersIterator> FDescribeQuestModelMastersIteratorPtr;

    class FDescribeQuestModelMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Quest::Model::FQuestModelMasterPtr>>,
        public TSharedFromThis<FDescribeQuestModelMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeQuestModelMastersIterator> Self;

    public:
        explicit FDescribeQuestModelMastersIteratorLoadTask(
            TSharedPtr<FDescribeQuestModelMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FQuestModelMasterPtr>>> Result
        ) override;
    };
}
