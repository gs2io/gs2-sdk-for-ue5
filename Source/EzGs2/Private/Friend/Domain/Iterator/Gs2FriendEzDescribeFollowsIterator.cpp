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

#include "EzGs2/Public/Friend/Domain/Iterator/Gs2FriendEzDescribeFollowsIterator.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

    FEzDescribeFollowsIterator::FEzDescribeFollowsIterator(
        const Gs2::Friend::Domain::Iterator::FDescribeFollowsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeFollowsIterator::FDescribeFollowsIteratorLoadTask::FDescribeFollowsIteratorLoadTask(
        const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeFollowsIterator::FDescribeFollowsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzFollowUser>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Friend::Model::FEzFollowUserPtr& FEzDescribeFollowsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Friend::Model::FEzFollowUserPtr FEzDescribeFollowsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeFollowsIterator::IteratorImpl& FEzDescribeFollowsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeFollowsIterator::IteratorImpl FEzDescribeFollowsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeFollowsIterator::IteratorImpl FEzDescribeFollowsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeFollowsIterator::FDescribeFollowsIteratorLoadTask>> FEzDescribeFollowsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeFollowsIteratorLoadTask>>(Iterator);
    }
}