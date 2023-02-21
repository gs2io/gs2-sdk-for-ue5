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

#include "EzGs2/Public/MegaField/Domain/Iterator/Gs2MegaFieldEzDescribeLayerModelsIterator.h"

namespace Gs2::UE5::MegaField::Domain::Iterator
{

    FEzDescribeLayerModelsIterator::FEzDescribeLayerModelsIterator(
        const Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeLayerModelsIterator::FDescribeLayerModelsIteratorLoadTask::FDescribeLayerModelsIteratorLoadTask(
        const TSharedPtr<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeLayerModelsIterator::FDescribeLayerModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::MegaField::Model::FEzLayerModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::MegaField::Model::FEzLayerModelPtr& FEzDescribeLayerModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::MegaField::Model::FEzLayerModelPtr FEzDescribeLayerModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeLayerModelsIterator::IteratorImpl& FEzDescribeLayerModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::MegaField::Model::FEzLayerModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeLayerModelsIterator::IteratorImpl FEzDescribeLayerModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::MegaField::Model::FEzLayerModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeLayerModelsIterator::IteratorImpl FEzDescribeLayerModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeLayerModelsIterator::FDescribeLayerModelsIteratorLoadTask>> FEzDescribeLayerModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeLayerModelsIteratorLoadTask>>(Iterator);
    }
}