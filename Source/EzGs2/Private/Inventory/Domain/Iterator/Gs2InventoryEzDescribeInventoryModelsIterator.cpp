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

#include "EzGs2/Public/Inventory/Domain/Iterator/Gs2InventoryEzDescribeInventoryModelsIterator.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

    FEzDescribeInventoryModelsIterator::FEzDescribeInventoryModelsIterator(
        const Gs2::Inventory::Domain::Iterator::FDescribeInventoryModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeInventoryModelsIterator::FDescribeInventoryModelsIteratorLoadTask::FDescribeInventoryModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeInventoryModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeInventoryModelsIterator::FDescribeInventoryModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventoryModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Inventory::Model::FEzInventoryModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Inventory::Model::FEzInventoryModelPtr& FEzDescribeInventoryModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Inventory::Model::FEzInventoryModelPtr FEzDescribeInventoryModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeInventoryModelsIterator::IteratorImpl& FEzDescribeInventoryModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Inventory::Model::FEzInventoryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeInventoryModelsIterator::IteratorImpl FEzDescribeInventoryModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Inventory::Model::FEzInventoryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeInventoryModelsIterator::IteratorImpl FEzDescribeInventoryModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeInventoryModelsIterator::FDescribeInventoryModelsIteratorLoadTask>> FEzDescribeInventoryModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeInventoryModelsIteratorLoadTask>>(Iterator);
    }
}