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

#include "EzGs2/Public/Distributor/Domain/Iterator/Gs2DistributorEzDescribeDistributorModelsIterator.h"

namespace Gs2::UE5::Distributor::Domain::Iterator
{

    FEzDescribeDistributorModelsIterator::FEzDescribeDistributorModelsIterator(
        const Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeDistributorModelsIterator::FDescribeDistributorModelsIteratorLoadTask::FDescribeDistributorModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeDistributorModelsIterator::FDescribeDistributorModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Model::FEzDistributorModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Distributor::Model::FEzDistributorModelPtr& FEzDescribeDistributorModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Distributor::Model::FEzDistributorModelPtr FEzDescribeDistributorModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeDistributorModelsIterator::IteratorImpl& FEzDescribeDistributorModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeDistributorModelsIterator::IteratorImpl FEzDescribeDistributorModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeDistributorModelsIterator::IteratorImpl FEzDescribeDistributorModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeDistributorModelsIterator::FDescribeDistributorModelsIteratorLoadTask>> FEzDescribeDistributorModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeDistributorModelsIteratorLoadTask>>(Iterator);
    }
}