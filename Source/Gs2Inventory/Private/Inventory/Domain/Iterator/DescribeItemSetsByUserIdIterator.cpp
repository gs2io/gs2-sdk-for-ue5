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

#include "Inventory/Domain/Iterator/DescribeItemSetsByUserIdIterator.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/Inventory.h"

namespace Gs2::Inventory::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeItemSetsByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeItemSetsByUserId(
            MakeShared<Gs2::Inventory::Request::FDescribeItemSetsByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithInventoryName(Self->InventoryName)
                ->WithUserId(Self->UserId)
                ->WithPageToken(Self->PageToken)
                ->WithLimit(Self->FetchSize)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = R->GetItems();
        Self->PageToken = R->GetNextPageToken();
        Self->Last = !Self->PageToken.IsSet();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeItemSetsByUserIdIteratorLoadTask>>
    FDescribeItemSetsByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeItemSetsByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeItemSetsByUserIdIterator::FDescribeItemSetsByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        UserId(UserId),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Inventory::Model::FItemSetPtr& FDescribeItemSetsByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Inventory::Model::FItemSetPtr FDescribeItemSetsByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeItemSetsByUserIdIterator::IteratorImpl& FDescribeItemSetsByUserIdIterator::IteratorImpl::operator++()
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

    FDescribeItemSetsByUserIdIterator::IteratorImpl FDescribeItemSetsByUserIdIterator::begin()
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
    FDescribeItemSetsByUserIdIterator::IteratorImpl FDescribeItemSetsByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

