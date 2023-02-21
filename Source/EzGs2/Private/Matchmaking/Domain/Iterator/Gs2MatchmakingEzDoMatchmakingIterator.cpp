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

#include "EzGs2/Public/Matchmaking/Domain/Iterator/Gs2MatchmakingEzDoMatchmakingIterator.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

    FEzDoMatchmakingIterator::FEzDoMatchmakingIterator(
        const Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDoMatchmakingIterator::FDoMatchmakingIteratorLoadTask::FDoMatchmakingIteratorLoadTask(
        const TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDoMatchmakingIterator::FDoMatchmakingIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGathering>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Matchmaking::Model::FEzGatheringPtr& FEzDoMatchmakingIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Matchmaking::Model::FEzGatheringPtr FEzDoMatchmakingIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDoMatchmakingIterator::IteratorImpl& FEzDoMatchmakingIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDoMatchmakingIterator::IteratorImpl FEzDoMatchmakingIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDoMatchmakingIterator::IteratorImpl FEzDoMatchmakingIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDoMatchmakingIterator::FDoMatchmakingIteratorLoadTask>> FEzDoMatchmakingIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDoMatchmakingIteratorLoadTask>>(Iterator);
    }
}