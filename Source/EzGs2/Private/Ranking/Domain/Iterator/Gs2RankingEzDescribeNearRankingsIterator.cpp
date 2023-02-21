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

#include "EzGs2/Public/Ranking/Domain/Iterator/Gs2RankingEzDescribeNearRankingsIterator.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

    FEzDescribeNearRankingsIterator::FEzDescribeNearRankingsIterator(
        const Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeNearRankingsIterator::FDescribeNearRankingsIteratorLoadTask::FDescribeNearRankingsIteratorLoadTask(
        const TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeNearRankingsIterator::FDescribeNearRankingsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzRanking>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Ranking::Model::FEzRankingPtr& FEzDescribeNearRankingsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Ranking::Model::FEzRankingPtr FEzDescribeNearRankingsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeNearRankingsIterator::IteratorImpl& FEzDescribeNearRankingsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeNearRankingsIterator::IteratorImpl FEzDescribeNearRankingsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeNearRankingsIterator::IteratorImpl FEzDescribeNearRankingsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeNearRankingsIterator::FDescribeNearRankingsIteratorLoadTask>> FEzDescribeNearRankingsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeNearRankingsIteratorLoadTask>>(Iterator);
    }
}