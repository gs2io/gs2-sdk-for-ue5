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

#include "EzGs2/Public/Mission/Domain/Iterator/Gs2MissionEzDescribeCompletesIterator.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

    FEzDescribeCompletesIterator::FEzDescribeCompletesIterator(
        const Gs2::Mission::Domain::Iterator::FDescribeCompletesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeCompletesIterator::FDescribeCompletesIteratorLoadTask::FDescribeCompletesIteratorLoadTask(
        const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeCompletesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeCompletesIterator::FDescribeCompletesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzComplete>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Mission::Model::FEzComplete::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Mission::Model::FEzCompletePtr& FEzDescribeCompletesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Mission::Model::FEzCompletePtr FEzDescribeCompletesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeCompletesIterator::IteratorImpl& FEzDescribeCompletesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Mission::Model::FEzComplete::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeCompletesIterator::IteratorImpl FEzDescribeCompletesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Mission::Model::FEzComplete::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeCompletesIterator::IteratorImpl FEzDescribeCompletesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeCompletesIterator::FDescribeCompletesIteratorLoadTask>> FEzDescribeCompletesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeCompletesIteratorLoadTask>>(Iterator);
    }
}