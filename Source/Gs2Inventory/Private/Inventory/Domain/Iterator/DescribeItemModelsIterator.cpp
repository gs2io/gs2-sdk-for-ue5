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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Inventory/Domain/Iterator/DescribeItemModelsIterator.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/InventoryModel.h"

namespace Gs2::Inventory::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeItemModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemModelPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeItemModels(
            MakeShared<Gs2::Inventory::Request::FDescribeItemModelsRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithInventoryName(Self->InventoryName)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = R->GetItems();
        Self->Last = true;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeItemModelsIteratorLoadTask>>
    FDescribeItemModelsIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeItemModelsIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeItemModelsIterator::FDescribeItemModelsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Inventory::Model::FItemModelPtr& FDescribeItemModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Inventory::Model::FItemModelPtr FDescribeItemModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeItemModelsIterator::IteratorImpl& FDescribeItemModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return *this;
    }

    FDescribeItemModelsIterator::IteratorImpl FDescribeItemModelsIterator::begin()
    {
        const auto Task = Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FDescribeItemModelsIterator::IteratorImpl FDescribeItemModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

