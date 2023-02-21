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

#include "Schedule/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/User.h"

namespace Gs2::Schedule::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeEventsByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Schedule::Model::FEventPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeEventsByUserId(
            MakeShared<Gs2::Schedule::Request::FDescribeEventsByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
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

    TSharedPtr<FAsyncTask<FDescribeEventsByUserIdIteratorLoadTask>>
    FDescribeEventsByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeEventsByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeEventsByUserIdIterator::FDescribeEventsByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Schedule::Model::FEventPtr& FDescribeEventsByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Schedule::Model::FEventPtr FDescribeEventsByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeEventsByUserIdIterator::IteratorImpl& FDescribeEventsByUserIdIterator::IteratorImpl::operator++()
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

    FDescribeEventsByUserIdIterator::IteratorImpl FDescribeEventsByUserIdIterator::begin()
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
    FDescribeEventsByUserIdIterator::IteratorImpl FDescribeEventsByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

