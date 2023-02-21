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

#include "EzGs2/Public/Exchange/Domain/Iterator/Gs2ExchangeEzDescribeRateModelsIterator.h"

namespace Gs2::UE5::Exchange::Domain::Iterator
{

    FEzDescribeRateModelsIterator::FEzDescribeRateModelsIterator(
        const Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeRateModelsIterator::FDescribeRateModelsIteratorLoadTask::FDescribeRateModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeRateModelsIterator::FDescribeRateModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzRateModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Exchange::Model::FEzRateModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Exchange::Model::FEzRateModelPtr& FEzDescribeRateModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Exchange::Model::FEzRateModelPtr FEzDescribeRateModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeRateModelsIterator::IteratorImpl& FEzDescribeRateModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Exchange::Model::FEzRateModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeRateModelsIterator::IteratorImpl FEzDescribeRateModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Exchange::Model::FEzRateModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeRateModelsIterator::IteratorImpl FEzDescribeRateModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeRateModelsIterator::FDescribeRateModelsIteratorLoadTask>> FEzDescribeRateModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeRateModelsIteratorLoadTask>>(Iterator);
    }
}