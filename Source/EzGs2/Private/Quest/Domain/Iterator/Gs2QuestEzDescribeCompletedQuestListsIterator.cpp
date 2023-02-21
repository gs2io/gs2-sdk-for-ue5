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

#include "EzGs2/Public/Quest/Domain/Iterator/Gs2QuestEzDescribeCompletedQuestListsIterator.h"

namespace Gs2::UE5::Quest::Domain::Iterator
{

    FEzDescribeCompletedQuestListsIterator::FEzDescribeCompletedQuestListsIterator(
        const Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeCompletedQuestListsIterator::FDescribeCompletedQuestListsIteratorLoadTask::FDescribeCompletedQuestListsIteratorLoadTask(
        const TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeCompletedQuestListsIterator::FDescribeCompletedQuestListsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzCompletedQuestList>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Quest::Model::FEzCompletedQuestList::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr& FEzDescribeCompletedQuestListsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr FEzDescribeCompletedQuestListsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeCompletedQuestListsIterator::IteratorImpl& FEzDescribeCompletedQuestListsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Quest::Model::FEzCompletedQuestList::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeCompletedQuestListsIterator::IteratorImpl FEzDescribeCompletedQuestListsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Quest::Model::FEzCompletedQuestList::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeCompletedQuestListsIterator::IteratorImpl FEzDescribeCompletedQuestListsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeCompletedQuestListsIterator::FDescribeCompletedQuestListsIteratorLoadTask>> FEzDescribeCompletedQuestListsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeCompletedQuestListsIteratorLoadTask>>(Iterator);
    }
}