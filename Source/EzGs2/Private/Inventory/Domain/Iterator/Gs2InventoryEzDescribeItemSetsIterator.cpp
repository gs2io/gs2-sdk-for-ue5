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

#include "EzGs2/Public/Inventory/Domain/Iterator/Gs2InventoryEzDescribeItemSetsIterator.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

    FEzDescribeItemSetsIterator::FEzDescribeItemSetsIterator(
        const Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeItemSetsIterator::FDescribeItemSetsIteratorLoadTask::FDescribeItemSetsIteratorLoadTask(
        const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeItemSetsIterator::FDescribeItemSetsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Inventory::Model::FEzItemSet::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Inventory::Model::FEzItemSetPtr& FEzDescribeItemSetsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Inventory::Model::FEzItemSetPtr FEzDescribeItemSetsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeItemSetsIterator::IteratorImpl& FEzDescribeItemSetsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Inventory::Model::FEzItemSet::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeItemSetsIterator::IteratorImpl FEzDescribeItemSetsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Inventory::Model::FEzItemSet::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeItemSetsIterator::IteratorImpl FEzDescribeItemSetsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeItemSetsIterator::FDescribeItemSetsIteratorLoadTask>> FEzDescribeItemSetsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeItemSetsIteratorLoadTask>>(Iterator);
    }
}