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

#include "EzGs2/Public/Version/Domain/Iterator/Gs2VersionEzDescribeAcceptVersionsIterator.h"

namespace Gs2::UE5::Version::Domain::Iterator
{

    FEzDescribeAcceptVersionsIterator::FEzDescribeAcceptVersionsIterator(
        const Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeAcceptVersionsIterator::FDescribeAcceptVersionsIteratorLoadTask::FDescribeAcceptVersionsIteratorLoadTask(
        const TSharedPtr<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeAcceptVersionsIterator::FDescribeAcceptVersionsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersion>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Version::Model::FEzAcceptVersion::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Version::Model::FEzAcceptVersionPtr& FEzDescribeAcceptVersionsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Version::Model::FEzAcceptVersionPtr FEzDescribeAcceptVersionsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeAcceptVersionsIterator::IteratorImpl& FEzDescribeAcceptVersionsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Version::Model::FEzAcceptVersion::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeAcceptVersionsIterator::IteratorImpl FEzDescribeAcceptVersionsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Version::Model::FEzAcceptVersion::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeAcceptVersionsIterator::IteratorImpl FEzDescribeAcceptVersionsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeAcceptVersionsIterator::FDescribeAcceptVersionsIteratorLoadTask>> FEzDescribeAcceptVersionsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeAcceptVersionsIteratorLoadTask>>(Iterator);
    }
}