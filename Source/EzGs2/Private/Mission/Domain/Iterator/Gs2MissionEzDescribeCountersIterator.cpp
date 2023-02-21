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

#include "EzGs2/Public/Mission/Domain/Iterator/Gs2MissionEzDescribeCountersIterator.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

    FEzDescribeCountersIterator::FEzDescribeCountersIterator(
        const Gs2::Mission::Domain::Iterator::FDescribeCountersIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeCountersIterator::FDescribeCountersIteratorLoadTask::FDescribeCountersIteratorLoadTask(
        const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeCountersIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeCountersIterator::FDescribeCountersIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounter>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Mission::Model::FEzCounter::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Mission::Model::FEzCounterPtr& FEzDescribeCountersIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Mission::Model::FEzCounterPtr FEzDescribeCountersIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeCountersIterator::IteratorImpl& FEzDescribeCountersIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Mission::Model::FEzCounter::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeCountersIterator::IteratorImpl FEzDescribeCountersIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Mission::Model::FEzCounter::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeCountersIterator::IteratorImpl FEzDescribeCountersIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeCountersIterator::FDescribeCountersIteratorLoadTask>> FEzDescribeCountersIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeCountersIteratorLoadTask>>(Iterator);
    }
}