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

#include "EzGs2/Public/Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeEntryModelsIterator.h"

namespace Gs2::UE5::Dictionary::Domain::Iterator
{

    FEzDescribeEntryModelsIterator::FEzDescribeEntryModelsIterator(
        const Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeEntryModelsIterator::FDescribeEntryModelsIteratorLoadTask::FDescribeEntryModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeEntryModelsIterator::FDescribeEntryModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Dictionary::Model::FEzEntryModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Dictionary::Model::FEzEntryModelPtr& FEzDescribeEntryModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Dictionary::Model::FEzEntryModelPtr FEzDescribeEntryModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeEntryModelsIterator::IteratorImpl& FEzDescribeEntryModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Dictionary::Model::FEzEntryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeEntryModelsIterator::IteratorImpl FEzDescribeEntryModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Dictionary::Model::FEzEntryModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeEntryModelsIterator::IteratorImpl FEzDescribeEntryModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeEntryModelsIterator::FDescribeEntryModelsIteratorLoadTask>> FEzDescribeEntryModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeEntryModelsIteratorLoadTask>>(Iterator);
    }
}