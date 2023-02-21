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

#include "EzGs2/Public/Stamina/Domain/Iterator/Gs2StaminaEzDescribeStaminaModelsIterator.h"

namespace Gs2::UE5::Stamina::Domain::Iterator
{

    FEzDescribeStaminaModelsIterator::FEzDescribeStaminaModelsIterator(
        const Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIteratorPtr Iterator
    ): Iterator(Iterator)
    {
    }

    FEzDescribeStaminaModelsIterator::FDescribeStaminaModelsIteratorLoadTask::FDescribeStaminaModelsIteratorLoadTask(
        const TSharedPtr<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator> Self
    ): Task(Self->Next())
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDescribeStaminaModelsIterator::FDescribeStaminaModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaModel>> Result
    )
    {
        Task->StartSynchronousTask();
        if (Task->GetTask().IsError())
        {
            return Task->GetTask().Error();
        }
        *Result = Gs2::UE5::Stamina::Model::FEzStaminaModel::FromModel(Task->GetTask().Result());
        return nullptr;
    }
    const Gs2::UE5::Stamina::Model::FEzStaminaModelPtr& FEzDescribeStaminaModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::UE5::Stamina::Model::FEzStaminaModelPtr FEzDescribeStaminaModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FEzDescribeStaminaModelsIterator::IteratorImpl& FEzDescribeStaminaModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Gs2::UE5::Stamina::Model::FEzStaminaModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return *this;
    }

    FEzDescribeStaminaModelsIterator::IteratorImpl FEzDescribeStaminaModelsIterator::begin()
    {
        const auto Task = Iterator->Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Gs2::UE5::Stamina::Model::FEzStaminaModel::FromModel(Task->GetTask().Result());
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FEzDescribeStaminaModelsIterator::IteratorImpl FEzDescribeStaminaModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }

    TSharedPtr<FAsyncTask<FEzDescribeStaminaModelsIterator::FDescribeStaminaModelsIteratorLoadTask>> FEzDescribeStaminaModelsIterator::Next() const
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeStaminaModelsIteratorLoadTask>>(Iterator);
    }
}