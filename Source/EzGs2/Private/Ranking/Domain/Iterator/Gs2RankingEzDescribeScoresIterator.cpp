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

#include "EzGs2/Public/Ranking/Domain/Iterator/Gs2RankingEzDescribeScoresIterator.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

    FEzDescribeScoresIterator::FEzDescribeScoresIterator(
        const Gs2::Ranking::Domain::Iterator::FDescribeScoresIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeScoresIterator::FDescribeScoresIteratorLoadTask::FDescribeScoresIteratorLoadTask(
        const TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeScoresIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeScoresIterator::FDescribeScoresIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzScore>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Ranking::Model::FEzScore::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Ranking::Model::FEzScorePtr& FEzDescribeScoresIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Ranking::Model::FEzScorePtr FEzDescribeScoresIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeScoresIterator::IteratorImpl& FEzDescribeScoresIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Ranking::Model::FEzScore::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeScoresIterator::IteratorImpl FEzDescribeScoresIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Ranking::Model::FEzScore::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeScoresIterator::IteratorImpl FEzDescribeScoresIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeScoresIterator::FDescribeScoresIteratorLoadTask>> FEzDescribeScoresIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeScoresIteratorLoadTask>>(Iterator);
    }
}