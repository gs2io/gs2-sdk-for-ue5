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

#include "EzGs2/Public/Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectsIterator.h"

namespace Gs2::UE5::Datastore::Domain::Iterator
{

    FEzDescribeDataObjectsIterator::FEzDescribeDataObjectsIterator(
        const Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeDataObjectsIterator::FDescribeDataObjectsIteratorLoadTask::FDescribeDataObjectsIteratorLoadTask(
        const TSharedPtr<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeDataObjectsIterator::FDescribeDataObjectsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObject>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Datastore::Model::FEzDataObjectPtr& FEzDescribeDataObjectsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Datastore::Model::FEzDataObjectPtr FEzDescribeDataObjectsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeDataObjectsIterator::IteratorImpl& FEzDescribeDataObjectsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeDataObjectsIterator::IteratorImpl FEzDescribeDataObjectsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeDataObjectsIterator::IteratorImpl FEzDescribeDataObjectsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeDataObjectsIterator::FDescribeDataObjectsIteratorLoadTask>> FEzDescribeDataObjectsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeDataObjectsIteratorLoadTask>>(Iterator);
    }
}