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

#include "EzGs2/Public/Lottery/Domain/Iterator/Gs2LotteryEzDescribeLotteryModelsIterator.h"

namespace Gs2::UE5::Lottery::Domain::Iterator
{

    FEzDescribeLotteryModelsIterator::FEzDescribeLotteryModelsIterator(
        const Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeLotteryModelsIterator::FDescribeLotteryModelsIteratorLoadTask::FDescribeLotteryModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeLotteryModelsIterator::FDescribeLotteryModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzLotteryModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Lottery::Model::FEzLotteryModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Lottery::Model::FEzLotteryModelPtr& FEzDescribeLotteryModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Lottery::Model::FEzLotteryModelPtr FEzDescribeLotteryModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeLotteryModelsIterator::IteratorImpl& FEzDescribeLotteryModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Lottery::Model::FEzLotteryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeLotteryModelsIterator::IteratorImpl FEzDescribeLotteryModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Lottery::Model::FEzLotteryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeLotteryModelsIterator::IteratorImpl FEzDescribeLotteryModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeLotteryModelsIterator::FDescribeLotteryModelsIteratorLoadTask>> FEzDescribeLotteryModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeLotteryModelsIteratorLoadTask>>(Iterator);
    }
}