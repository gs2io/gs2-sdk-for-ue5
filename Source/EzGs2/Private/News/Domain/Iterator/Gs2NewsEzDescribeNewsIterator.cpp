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

#include "EzGs2/Public/News/Domain/Iterator/Gs2NewsEzDescribeNewsIterator.h"

namespace Gs2::UE5::News::Domain::Iterator
{

    FEzDescribeNewsIterator::FEzDescribeNewsIterator(
        const Gs2::News::Domain::Iterator::FDescribeNewsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeNewsIterator::FDescribeNewsIteratorLoadTask::FDescribeNewsIteratorLoadTask(
        const TSharedPtr<Gs2::News::Domain::Iterator::FDescribeNewsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeNewsIterator::FDescribeNewsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::News::Model::FEzNews>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::News::Model::FEzNews::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::News::Model::FEzNewsPtr& FEzDescribeNewsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::News::Model::FEzNewsPtr FEzDescribeNewsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeNewsIterator::IteratorImpl& FEzDescribeNewsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::News::Model::FEzNews::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeNewsIterator::IteratorImpl FEzDescribeNewsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::News::Model::FEzNews::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeNewsIterator::IteratorImpl FEzDescribeNewsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeNewsIterator::FDescribeNewsIteratorLoadTask>> FEzDescribeNewsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeNewsIteratorLoadTask>>(Iterator);
    }
}