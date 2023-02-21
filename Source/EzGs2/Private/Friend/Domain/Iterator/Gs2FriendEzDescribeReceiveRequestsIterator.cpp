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

#include "EzGs2/Public/Friend/Domain/Iterator/Gs2FriendEzDescribeReceiveRequestsIterator.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

    FEzDescribeReceiveRequestsIterator::FEzDescribeReceiveRequestsIterator(
        const Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeReceiveRequestsIterator::FDescribeReceiveRequestsIteratorLoadTask::FDescribeReceiveRequestsIteratorLoadTask(
        const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeReceiveRequestsIterator::FDescribeReceiveRequestsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendRequest>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Friend::Model::FEzFriendRequestPtr& FEzDescribeReceiveRequestsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Friend::Model::FEzFriendRequestPtr FEzDescribeReceiveRequestsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeReceiveRequestsIterator::IteratorImpl& FEzDescribeReceiveRequestsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeReceiveRequestsIterator::IteratorImpl FEzDescribeReceiveRequestsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeReceiveRequestsIterator::IteratorImpl FEzDescribeReceiveRequestsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeReceiveRequestsIterator::FDescribeReceiveRequestsIteratorLoadTask>> FEzDescribeReceiveRequestsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeReceiveRequestsIteratorLoadTask>>(Iterator);
    }
}