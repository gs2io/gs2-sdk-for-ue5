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

#include "EzGs2/Public/Friend/Domain/Iterator/Gs2FriendEzDescribeBlackListIterator.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

    FEzDescribeBlackListIterator::FEzDescribeBlackListIterator(
        const Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeBlackListIterator::FDescribeBlackListIteratorLoadTask::FDescribeBlackListIteratorLoadTask(
        const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeBlackListIterator::FDescribeBlackListIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FBlackListEntry>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Task->GetTask().Result();
        return nullptr;
    }
    const Gs2::Friend::Model::FBlackListEntryPtr& FEzDescribeBlackListIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Friend::Model::FBlackListEntryPtr FEzDescribeBlackListIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeBlackListIterator::IteratorImpl& FEzDescribeBlackListIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeBlackListIterator::IteratorImpl FEzDescribeBlackListIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeBlackListIterator::IteratorImpl FEzDescribeBlackListIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeBlackListIterator::FDescribeBlackListIteratorLoadTask>> FEzDescribeBlackListIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeBlackListIteratorLoadTask>>(Iterator);
    }
}