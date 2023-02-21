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

#include "EzGs2/Public/Inbox/Domain/Iterator/Gs2InboxEzDescribeMessagesIterator.h"

namespace Gs2::UE5::Inbox::Domain::Iterator
{

    FEzDescribeMessagesIterator::FEzDescribeMessagesIterator(
        const Gs2::Inbox::Domain::Iterator::FDescribeMessagesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeMessagesIterator::FDescribeMessagesIteratorLoadTask::FDescribeMessagesIteratorLoadTask(
        const TSharedPtr<Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeMessagesIterator::FDescribeMessagesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inbox::Model::FEzMessage>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Inbox::Model::FEzMessagePtr& FEzDescribeMessagesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Inbox::Model::FEzMessagePtr FEzDescribeMessagesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeMessagesIterator::IteratorImpl& FEzDescribeMessagesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeMessagesIterator::IteratorImpl FEzDescribeMessagesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeMessagesIterator::IteratorImpl FEzDescribeMessagesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeMessagesIterator::FDescribeMessagesIteratorLoadTask>> FEzDescribeMessagesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeMessagesIteratorLoadTask>>(Iterator);
    }
}