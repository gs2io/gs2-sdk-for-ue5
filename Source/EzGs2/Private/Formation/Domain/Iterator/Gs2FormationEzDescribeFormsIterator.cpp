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

#include "EzGs2/Public/Formation/Domain/Iterator/Gs2FormationEzDescribeFormsIterator.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

    FEzDescribeFormsIterator::FEzDescribeFormsIterator(
        const Gs2::Formation::Domain::Iterator::FDescribeFormsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeFormsIterator::FDescribeFormsIteratorLoadTask::FDescribeFormsIteratorLoadTask(
        const TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribeFormsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeFormsIterator::FDescribeFormsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzForm>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Formation::Model::FEzForm::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Formation::Model::FEzFormPtr& FEzDescribeFormsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Formation::Model::FEzFormPtr FEzDescribeFormsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeFormsIterator::IteratorImpl& FEzDescribeFormsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Formation::Model::FEzForm::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeFormsIterator::IteratorImpl FEzDescribeFormsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Formation::Model::FEzForm::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeFormsIterator::IteratorImpl FEzDescribeFormsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeFormsIterator::FDescribeFormsIteratorLoadTask>> FEzDescribeFormsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeFormsIteratorLoadTask>>(Iterator);
    }
}