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

#include "EzGs2/Public/Formation/Domain/Iterator/Gs2FormationEzDescribePropertyFormsIterator.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

    FEzDescribePropertyFormsIterator::FEzDescribePropertyFormsIterator(
        const Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribePropertyFormsIterator::FDescribePropertyFormsIteratorLoadTask::FDescribePropertyFormsIteratorLoadTask(
        const TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribePropertyFormsIterator::FDescribePropertyFormsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyForm>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Formation::Model::FEzPropertyFormPtr& FEzDescribePropertyFormsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Formation::Model::FEzPropertyFormPtr FEzDescribePropertyFormsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribePropertyFormsIterator::IteratorImpl& FEzDescribePropertyFormsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribePropertyFormsIterator::IteratorImpl FEzDescribePropertyFormsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribePropertyFormsIterator::IteratorImpl FEzDescribePropertyFormsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribePropertyFormsIterator::FDescribePropertyFormsIteratorLoadTask>> FEzDescribePropertyFormsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribePropertyFormsIteratorLoadTask>>(Iterator);
    }
}