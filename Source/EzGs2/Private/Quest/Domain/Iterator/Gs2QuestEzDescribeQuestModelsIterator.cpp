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

#include "EzGs2/Public/Quest/Domain/Iterator/Gs2QuestEzDescribeQuestModelsIterator.h"

namespace Gs2::UE5::Quest::Domain::Iterator
{

    FEzDescribeQuestModelsIterator::FEzDescribeQuestModelsIterator(
        const Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeQuestModelsIterator::FDescribeQuestModelsIteratorLoadTask::FDescribeQuestModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeQuestModelsIterator::FDescribeQuestModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Quest::Model::FEzQuestModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Quest::Model::FEzQuestModelPtr& FEzDescribeQuestModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Quest::Model::FEzQuestModelPtr FEzDescribeQuestModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeQuestModelsIterator::IteratorImpl& FEzDescribeQuestModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Quest::Model::FEzQuestModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeQuestModelsIterator::IteratorImpl FEzDescribeQuestModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Quest::Model::FEzQuestModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeQuestModelsIterator::IteratorImpl FEzDescribeQuestModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeQuestModelsIterator::FDescribeQuestModelsIteratorLoadTask>> FEzDescribeQuestModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeQuestModelsIteratorLoadTask>>(Iterator);
    }
}