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

#include "EzGs2/Public/Mission/Domain/Iterator/Gs2MissionEzDescribeCounterModelsIterator.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

    FEzDescribeCounterModelsIterator::FEzDescribeCounterModelsIterator(
        const Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeCounterModelsIterator::FDescribeCounterModelsIteratorLoadTask::FDescribeCounterModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeCounterModelsIterator::FDescribeCounterModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Mission::Model::FEzCounterModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Mission::Model::FEzCounterModelPtr& FEzDescribeCounterModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Mission::Model::FEzCounterModelPtr FEzDescribeCounterModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeCounterModelsIterator::IteratorImpl& FEzDescribeCounterModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Mission::Model::FEzCounterModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeCounterModelsIterator::IteratorImpl FEzDescribeCounterModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Mission::Model::FEzCounterModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeCounterModelsIterator::IteratorImpl FEzDescribeCounterModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeCounterModelsIterator::FDescribeCounterModelsIteratorLoadTask>> FEzDescribeCounterModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeCounterModelsIteratorLoadTask>>(Iterator);
    }
}