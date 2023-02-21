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

#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ItemSet.h"

namespace Gs2::Inventory::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReferenceOfIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FReferenceOfEntryPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeReferenceOf(
            MakeShared<Gs2::Inventory::Request::FDescribeReferenceOfRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithInventoryName(Self->InventoryName)
                ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                ->WithItemName(Self->ItemName)
                ->WithItemSetName(Self->ItemSetName)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (!(*Result).IsValid())
        {
            *Result = MakeShared<TArray<Inventory::Model::FReferenceOfEntryPtr>>();
        }
        for (auto Item : *R->GetItems())
        {
            (*Result)->Add(MakeShared<Inventory::Model::FReferenceOfEntry>(Item));
        }
        Self->Last = true;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeReferenceOfIteratorLoadTask>>
    FDescribeReferenceOfIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeReferenceOfIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeReferenceOfIterator::FDescribeReferenceOfIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        AccessToken(AccessToken),
        ItemName(ItemName),
        ItemSetName(ItemSetName),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Inventory::Model::FReferenceOfEntryPtr& FDescribeReferenceOfIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Inventory::Model::FReferenceOfEntryPtr FDescribeReferenceOfIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeReferenceOfIterator::IteratorImpl& FDescribeReferenceOfIterator::IteratorImpl::operator++()
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

    FDescribeReferenceOfIterator::IteratorImpl FDescribeReferenceOfIterator::begin()
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
    FDescribeReferenceOfIterator::IteratorImpl FDescribeReferenceOfIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

