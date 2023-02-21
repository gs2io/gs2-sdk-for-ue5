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

#include "EzGs2/Public/Formation/Domain/Iterator/Gs2FormationEzDescribeMoldModelsIterator.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

    FEzDescribeMoldModelsIterator::FEzDescribeMoldModelsIterator(
        const Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeMoldModelsIterator::FDescribeMoldModelsIteratorLoadTask::FDescribeMoldModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeMoldModelsIterator::FDescribeMoldModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Formation::Model::FEzMoldModelPtr& FEzDescribeMoldModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Formation::Model::FEzMoldModelPtr FEzDescribeMoldModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeMoldModelsIterator::IteratorImpl& FEzDescribeMoldModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeMoldModelsIterator::IteratorImpl FEzDescribeMoldModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeMoldModelsIterator::IteratorImpl FEzDescribeMoldModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeMoldModelsIterator::FDescribeMoldModelsIteratorLoadTask>> FEzDescribeMoldModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeMoldModelsIteratorLoadTask>>(Iterator);
    }
}