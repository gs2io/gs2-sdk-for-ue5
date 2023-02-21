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

#include "EzGs2/Public/Account/Domain/Iterator/Gs2AccountEzDescribeTakeOversIterator.h"

namespace Gs2::UE5::Account::Domain::Iterator
{

    FEzDescribeTakeOversIterator::FEzDescribeTakeOversIterator(
        const Gs2::Account::Domain::Iterator::FDescribeTakeOversIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeTakeOversIterator::FDescribeTakeOversIteratorLoadTask::FDescribeTakeOversIteratorLoadTask(
        const TSharedPtr<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeTakeOversIterator::FDescribeTakeOversIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOver>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Account::Model::FEzTakeOver::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Account::Model::FEzTakeOverPtr& FEzDescribeTakeOversIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Account::Model::FEzTakeOverPtr FEzDescribeTakeOversIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeTakeOversIterator::IteratorImpl& FEzDescribeTakeOversIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Account::Model::FEzTakeOver::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeTakeOversIterator::IteratorImpl FEzDescribeTakeOversIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Account::Model::FEzTakeOver::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeTakeOversIterator::IteratorImpl FEzDescribeTakeOversIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeTakeOversIterator::FDescribeTakeOversIteratorLoadTask>> FEzDescribeTakeOversIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeTakeOversIteratorLoadTask>>(Iterator);
    }
}