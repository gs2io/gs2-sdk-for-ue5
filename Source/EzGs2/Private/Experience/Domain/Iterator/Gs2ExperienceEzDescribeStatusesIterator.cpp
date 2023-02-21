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

#include "EzGs2/Public/Experience/Domain/Iterator/Gs2ExperienceEzDescribeStatusesIterator.h"

namespace Gs2::UE5::Experience::Domain::Iterator
{

    FEzDescribeStatusesIterator::FEzDescribeStatusesIterator(
        const Gs2::Experience::Domain::Iterator::FDescribeStatusesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeStatusesIterator::FDescribeStatusesIteratorLoadTask::FDescribeStatusesIteratorLoadTask(
        const TSharedPtr<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeStatusesIterator::FDescribeStatusesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Experience::Model::FEzStatus>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Experience::Model::FEzStatus::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Experience::Model::FEzStatusPtr& FEzDescribeStatusesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Experience::Model::FEzStatusPtr FEzDescribeStatusesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeStatusesIterator::IteratorImpl& FEzDescribeStatusesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Experience::Model::FEzStatus::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeStatusesIterator::IteratorImpl FEzDescribeStatusesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Experience::Model::FEzStatus::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeStatusesIterator::IteratorImpl FEzDescribeStatusesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeStatusesIterator::FDescribeStatusesIteratorLoadTask>> FEzDescribeStatusesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeStatusesIteratorLoadTask>>(Iterator);
    }
}