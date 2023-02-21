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

#include "EzGs2/Public/Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeRatingsIterator.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

    FEzDescribeRatingsIterator::FEzDescribeRatingsIterator(
        const Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeRatingsIterator::FDescribeRatingsIteratorLoadTask::FDescribeRatingsIteratorLoadTask(
        const TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeRatingsIterator::FDescribeRatingsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRating>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Matchmaking::Model::FEzRating::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Matchmaking::Model::FEzRatingPtr& FEzDescribeRatingsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Matchmaking::Model::FEzRatingPtr FEzDescribeRatingsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeRatingsIterator::IteratorImpl& FEzDescribeRatingsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Matchmaking::Model::FEzRating::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeRatingsIterator::IteratorImpl FEzDescribeRatingsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Matchmaking::Model::FEzRating::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeRatingsIterator::IteratorImpl FEzDescribeRatingsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeRatingsIterator::FDescribeRatingsIteratorLoadTask>> FEzDescribeRatingsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeRatingsIteratorLoadTask>>(Iterator);
    }
}