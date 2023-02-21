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

#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameAndUserIdIterator.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/User.h"

namespace Gs2::Ranking::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeSubscribesByCategoryNameAndUserId(
            MakeShared<Gs2::Ranking::Request::FDescribeSubscribesByCategoryNameAndUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithCategoryName(Self->CategoryName)
                ->WithUserId(Self->UserId)
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

    TSharedPtr<FAsyncTask<FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask>>
    FDescribeSubscribesByCategoryNameAndUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FDescribeSubscribesByCategoryNameAndUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Ranking::FGs2RankingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        UserId(UserId),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Ranking::Model::FSubscribeUserPtr& FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Ranking::Model::FSubscribeUserPtr FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl& FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl::operator++()
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

    FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl FDescribeSubscribesByCategoryNameAndUserIdIterator::begin()
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
    FDescribeSubscribesByCategoryNameAndUserIdIterator::IteratorImpl FDescribeSubscribesByCategoryNameAndUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

