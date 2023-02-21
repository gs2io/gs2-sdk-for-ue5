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

#include "EzGs2/Public/Chat/Domain/Iterator/Gs2ChatEzDescribeSubscribesIterator.h"

namespace Gs2::UE5::Chat::Domain::Iterator
{

    FEzDescribeSubscribesIterator::FEzDescribeSubscribesIterator(
        const Gs2::Chat::Domain::Iterator::FDescribeSubscribesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeSubscribesIterator::FDescribeSubscribesIteratorLoadTask::FDescribeSubscribesIteratorLoadTask(
        const TSharedPtr<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeSubscribesIterator::FDescribeSubscribesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Model::FEzSubscribe>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Chat::Model::FEzSubscribe::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Chat::Model::FEzSubscribePtr& FEzDescribeSubscribesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Chat::Model::FEzSubscribePtr FEzDescribeSubscribesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeSubscribesIterator::IteratorImpl& FEzDescribeSubscribesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Chat::Model::FEzSubscribe::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeSubscribesIterator::IteratorImpl FEzDescribeSubscribesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Chat::Model::FEzSubscribe::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeSubscribesIterator::IteratorImpl FEzDescribeSubscribesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeSubscribesIterator::FDescribeSubscribesIteratorLoadTask>> FEzDescribeSubscribesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeSubscribesIteratorLoadTask>>(Iterator);
    }
}