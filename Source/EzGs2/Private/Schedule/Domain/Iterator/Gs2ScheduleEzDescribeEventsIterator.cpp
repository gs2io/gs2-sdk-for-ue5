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

#include "EzGs2/Public/Schedule/Domain/Iterator/Gs2ScheduleEzDescribeEventsIterator.h"

namespace Gs2::UE5::Schedule::Domain::Iterator
{

    FEzDescribeEventsIterator::FEzDescribeEventsIterator(
        const Gs2::Schedule::Domain::Iterator::FDescribeEventsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeEventsIterator::FDescribeEventsIteratorLoadTask::FDescribeEventsIteratorLoadTask(
        const TSharedPtr<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeEventsIterator::FDescribeEventsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Schedule::Model::FEzEvent>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Schedule::Model::FEzEvent::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Schedule::Model::FEzEventPtr& FEzDescribeEventsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Schedule::Model::FEzEventPtr FEzDescribeEventsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeEventsIterator::IteratorImpl& FEzDescribeEventsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Schedule::Model::FEzEvent::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeEventsIterator::IteratorImpl FEzDescribeEventsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Schedule::Model::FEzEvent::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeEventsIterator::IteratorImpl FEzDescribeEventsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeEventsIterator::FDescribeEventsIteratorLoadTask>> FEzDescribeEventsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeEventsIteratorLoadTask>>(Iterator);
    }
}