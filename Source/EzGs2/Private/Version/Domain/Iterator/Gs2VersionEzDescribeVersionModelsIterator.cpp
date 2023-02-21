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

#include "EzGs2/Public/Version/Domain/Iterator/Gs2VersionEzDescribeVersionModelsIterator.h"

namespace Gs2::UE5::Version::Domain::Iterator
{

    FEzDescribeVersionModelsIterator::FEzDescribeVersionModelsIterator(
        const Gs2::Version::Domain::Iterator::FDescribeVersionModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeVersionModelsIterator::FDescribeVersionModelsIteratorLoadTask::FDescribeVersionModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Version::Domain::Iterator::FDescribeVersionModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeVersionModelsIterator::FDescribeVersionModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Version::Model::FEzVersionModelPtr& FEzDescribeVersionModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Version::Model::FEzVersionModelPtr FEzDescribeVersionModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeVersionModelsIterator::IteratorImpl& FEzDescribeVersionModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeVersionModelsIterator::IteratorImpl FEzDescribeVersionModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeVersionModelsIterator::IteratorImpl FEzDescribeVersionModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeVersionModelsIterator::FDescribeVersionModelsIteratorLoadTask>> FEzDescribeVersionModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeVersionModelsIteratorLoadTask>>(Iterator);
    }
}