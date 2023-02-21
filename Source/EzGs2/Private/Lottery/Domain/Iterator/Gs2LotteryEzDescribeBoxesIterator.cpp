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

#include "EzGs2/Public/Lottery/Domain/Iterator/Gs2LotteryEzDescribeBoxesIterator.h"

namespace Gs2::UE5::Lottery::Domain::Iterator
{

    FEzDescribeBoxesIterator::FEzDescribeBoxesIterator(
        const Gs2::Lottery::Domain::Iterator::FDescribeBoxesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeBoxesIterator::FDescribeBoxesIteratorLoadTask::FDescribeBoxesIteratorLoadTask(
        const TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeBoxesIterator::FDescribeBoxesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItems>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Lottery::Model::FEzBoxItemsPtr& FEzDescribeBoxesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Lottery::Model::FEzBoxItemsPtr FEzDescribeBoxesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeBoxesIterator::IteratorImpl& FEzDescribeBoxesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeBoxesIterator::IteratorImpl FEzDescribeBoxesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeBoxesIterator::IteratorImpl FEzDescribeBoxesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeBoxesIterator::FDescribeBoxesIteratorLoadTask>> FEzDescribeBoxesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeBoxesIteratorLoadTask>>(Iterator);
    }
}