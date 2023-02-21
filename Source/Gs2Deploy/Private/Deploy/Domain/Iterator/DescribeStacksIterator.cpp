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

#include "Deploy/Domain/Iterator/DescribeStacksIterator.h"
#include "Deploy/Domain/Model/Stack.h"

namespace Gs2::Deploy::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeStacksIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Deploy::Model::FStackPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeStacks(
            MakeShared<Gs2::Deploy::Request::FDescribeStacksRequest>()
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

    TSharedPtr<FAsyncTask<FDescribeStacksIteratorLoadTask>>
    FDescribeStacksIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeStacksIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeStacksIterator::FDescribeStacksIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Deploy::FGs2DeployRestClientPtr Client
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Deploy::Model::FStackPtr& FDescribeStacksIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Deploy::Model::FStackPtr FDescribeStacksIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeStacksIterator::IteratorImpl& FDescribeStacksIterator::IteratorImpl::operator++()
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

    FDescribeStacksIterator::IteratorImpl FDescribeStacksIterator::begin()
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
    FDescribeStacksIterator::IteratorImpl FDescribeStacksIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

