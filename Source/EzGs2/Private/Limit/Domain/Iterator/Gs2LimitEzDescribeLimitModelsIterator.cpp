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

#include "EzGs2/Public/Limit/Domain/Iterator/Gs2LimitEzDescribeLimitModelsIterator.h"

namespace Gs2::UE5::Limit::Domain::Iterator
{

    FEzDescribeLimitModelsIterator::FEzDescribeLimitModelsIterator(
        const Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeLimitModelsIterator::FDescribeLimitModelsIteratorLoadTask::FDescribeLimitModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeLimitModelsIterator::FDescribeLimitModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Model::FEzLimitModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Limit::Model::FEzLimitModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Limit::Model::FEzLimitModelPtr& FEzDescribeLimitModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Limit::Model::FEzLimitModelPtr FEzDescribeLimitModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeLimitModelsIterator::IteratorImpl& FEzDescribeLimitModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Limit::Model::FEzLimitModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeLimitModelsIterator::IteratorImpl FEzDescribeLimitModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Limit::Model::FEzLimitModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeLimitModelsIterator::IteratorImpl FEzDescribeLimitModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeLimitModelsIterator::FDescribeLimitModelsIteratorLoadTask>> FEzDescribeLimitModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeLimitModelsIteratorLoadTask>>(Iterator);
    }
}