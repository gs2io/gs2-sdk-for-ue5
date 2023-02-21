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

#include "EzGs2/Public/Inventory/Domain/Iterator/Gs2InventoryEzDescribeItemModelsIterator.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

    FEzDescribeItemModelsIterator::FEzDescribeItemModelsIterator(
        const Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeItemModelsIterator::FDescribeItemModelsIteratorLoadTask::FDescribeItemModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeItemModelsIterator::FDescribeItemModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Inventory::Model::FEzItemModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Inventory::Model::FEzItemModelPtr& FEzDescribeItemModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Inventory::Model::FEzItemModelPtr FEzDescribeItemModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeItemModelsIterator::IteratorImpl& FEzDescribeItemModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Inventory::Model::FEzItemModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeItemModelsIterator::IteratorImpl FEzDescribeItemModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Inventory::Model::FEzItemModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeItemModelsIterator::IteratorImpl FEzDescribeItemModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeItemModelsIterator::FDescribeItemModelsIteratorLoadTask>> FEzDescribeItemModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeItemModelsIteratorLoadTask>>(Iterator);
    }
}