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

#include "EzGs2/Public/Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeRatingModelsIterator.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

    FEzDescribeRatingModelsIterator::FEzDescribeRatingModelsIterator(
        const Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeRatingModelsIterator::FDescribeRatingModelsIteratorLoadTask::FDescribeRatingModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeRatingModelsIterator::FDescribeRatingModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRatingModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Matchmaking::Model::FEzRatingModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr& FEzDescribeRatingModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr FEzDescribeRatingModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeRatingModelsIterator::IteratorImpl& FEzDescribeRatingModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Matchmaking::Model::FEzRatingModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeRatingModelsIterator::IteratorImpl FEzDescribeRatingModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Matchmaking::Model::FEzRatingModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeRatingModelsIterator::IteratorImpl FEzDescribeRatingModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeRatingModelsIterator::FDescribeRatingModelsIteratorLoadTask>> FEzDescribeRatingModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeRatingModelsIteratorLoadTask>>(Iterator);
    }
}