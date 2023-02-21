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

#include "EzGs2/Public/Formation/Domain/Iterator/Gs2FormationEzDescribeFormModelsIterator.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

    FEzDescribeFormModelsIterator::FEzDescribeFormModelsIterator(
        const Gs2::Formation::Domain::Iterator::FDescribeFormModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeFormModelsIterator::FDescribeFormModelsIteratorLoadTask::FDescribeFormModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribeFormModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeFormModelsIterator::FDescribeFormModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Formation::Model::FEzFormModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Formation::Model::FEzFormModelPtr& FEzDescribeFormModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Formation::Model::FEzFormModelPtr FEzDescribeFormModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeFormModelsIterator::IteratorImpl& FEzDescribeFormModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Formation::Model::FEzFormModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeFormModelsIterator::IteratorImpl FEzDescribeFormModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Formation::Model::FEzFormModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeFormModelsIterator::IteratorImpl FEzDescribeFormModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeFormModelsIterator::FDescribeFormModelsIteratorLoadTask>> FEzDescribeFormModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeFormModelsIteratorLoadTask>>(Iterator);
    }
}