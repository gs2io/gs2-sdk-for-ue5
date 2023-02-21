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

#include "EzGs2/Public/Friend/Domain/Iterator/Gs2FriendEzDescribeSendRequestsIterator.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

    FEzDescribeSendRequestsIterator::FEzDescribeSendRequestsIterator(
        const Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeSendRequestsIterator::FDescribeSendRequestsIteratorLoadTask::FDescribeSendRequestsIteratorLoadTask(
        const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeSendRequestsIterator::FDescribeSendRequestsIteratorLoadTask::Action(
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
    const Gs2::UE5::Friend::Model::FEzFriendRequestPtr& FEzDescribeSendRequestsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Friend::Model::FEzFriendRequestPtr FEzDescribeSendRequestsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeSendRequestsIterator::IteratorImpl& FEzDescribeSendRequestsIterator::IteratorImpl::operator++()
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

    FEzDescribeSendRequestsIterator::IteratorImpl FEzDescribeSendRequestsIterator::begin()
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
    FEzDescribeSendRequestsIterator::IteratorImpl FEzDescribeSendRequestsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeSendRequestsIterator::FDescribeSendRequestsIteratorLoadTask>> FEzDescribeSendRequestsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeSendRequestsIteratorLoadTask>>(Iterator);
    }
}