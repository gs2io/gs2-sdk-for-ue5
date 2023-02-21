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

#include "EzGs2/Public/Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectHistoriesIterator.h"

namespace Gs2::UE5::Datastore::Domain::Iterator
{

    FEzDescribeDataObjectHistoriesIterator::FEzDescribeDataObjectHistoriesIterator(
        const Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeDataObjectHistoriesIterator::FDescribeDataObjectHistoriesIteratorLoadTask::FDescribeDataObjectHistoriesIteratorLoadTask(
        const TSharedPtr<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeDataObjectHistoriesIterator::FDescribeDataObjectHistoriesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectHistory>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Datastore::Model::FEzDataObjectHistory::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr& FEzDescribeDataObjectHistoriesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr FEzDescribeDataObjectHistoriesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeDataObjectHistoriesIterator::IteratorImpl& FEzDescribeDataObjectHistoriesIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Datastore::Model::FEzDataObjectHistory::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeDataObjectHistoriesIterator::IteratorImpl FEzDescribeDataObjectHistoriesIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Datastore::Model::FEzDataObjectHistory::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeDataObjectHistoriesIterator::IteratorImpl FEzDescribeDataObjectHistoriesIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeDataObjectHistoriesIterator::FDescribeDataObjectHistoriesIteratorLoadTask>> FEzDescribeDataObjectHistoriesIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeDataObjectHistoriesIteratorLoadTask>>(Iterator);
    }
}