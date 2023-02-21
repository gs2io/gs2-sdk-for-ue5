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

#include "EzGs2/Public/Exchange/Domain/Iterator/Gs2ExchangeEzDescribeAwaitsIterator.h"

namespace Gs2::UE5::Exchange::Domain::Iterator
{

    FEzDescribeAwaitsIterator::FEzDescribeAwaitsIterator(
        const Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeAwaitsIterator::FDescribeAwaitsIteratorLoadTask::FDescribeAwaitsIteratorLoadTask(
        const TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeAwaitsIterator::FDescribeAwaitsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwait>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Exchange::Model::FEzAwait::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Exchange::Model::FEzAwaitPtr& FEzDescribeAwaitsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Exchange::Model::FEzAwaitPtr FEzDescribeAwaitsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeAwaitsIterator::IteratorImpl& FEzDescribeAwaitsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Exchange::Model::FEzAwait::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeAwaitsIterator::IteratorImpl FEzDescribeAwaitsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Exchange::Model::FEzAwait::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeAwaitsIterator::IteratorImpl FEzDescribeAwaitsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeAwaitsIterator::FDescribeAwaitsIteratorLoadTask>> FEzDescribeAwaitsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeAwaitsIteratorLoadTask>>(Iterator);
    }
}