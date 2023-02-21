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

#include "EzGs2/Public/Inventory/Domain/Iterator/Gs2InventoryEzDescribeInventoriesIterator.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

    FEzDescribeInventoriesIterator::FEzDescribeInventoriesIterator(
        const Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeInventoriesIterator::FDescribeInventoriesIteratorLoadTask::FDescribeInventoriesIteratorLoadTask(
        const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeInventoriesIterator::FDescribeInventoriesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventory>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Inventory::Model::FEzInventoryPtr& FEzDescribeInventoriesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Inventory::Model::FEzInventoryPtr FEzDescribeInventoriesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeInventoriesIterator::IteratorImpl& FEzDescribeInventoriesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeInventoriesIterator::IteratorImpl FEzDescribeInventoriesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeInventoriesIterator::IteratorImpl FEzDescribeInventoriesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeInventoriesIterator::FDescribeInventoriesIteratorLoadTask>> FEzDescribeInventoriesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeInventoriesIteratorLoadTask>>(Iterator);
    }
}