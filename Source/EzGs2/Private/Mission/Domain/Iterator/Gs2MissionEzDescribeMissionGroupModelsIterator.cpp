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

#include "EzGs2/Public/Mission/Domain/Iterator/Gs2MissionEzDescribeMissionGroupModelsIterator.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

    FEzDescribeMissionGroupModelsIterator::FEzDescribeMissionGroupModelsIterator(
        const Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeMissionGroupModelsIterator::FDescribeMissionGroupModelsIteratorLoadTask::FDescribeMissionGroupModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeMissionGroupModelsIterator::FDescribeMissionGroupModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionGroupModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Mission::Model::FEzMissionGroupModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr& FEzDescribeMissionGroupModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr FEzDescribeMissionGroupModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeMissionGroupModelsIterator::IteratorImpl& FEzDescribeMissionGroupModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Mission::Model::FEzMissionGroupModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeMissionGroupModelsIterator::IteratorImpl FEzDescribeMissionGroupModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Mission::Model::FEzMissionGroupModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeMissionGroupModelsIterator::IteratorImpl FEzDescribeMissionGroupModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeMissionGroupModelsIterator::FDescribeMissionGroupModelsIteratorLoadTask>> FEzDescribeMissionGroupModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeMissionGroupModelsIteratorLoadTask>>(Iterator);
    }
}