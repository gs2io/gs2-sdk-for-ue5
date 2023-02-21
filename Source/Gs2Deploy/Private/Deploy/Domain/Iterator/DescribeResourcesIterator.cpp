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

#include "Deploy/Domain/Iterator/DescribeResourcesIterator.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Stack.h"

namespace Gs2::Deploy::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeResourcesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Deploy::Model::FResourcePtr>>> Result)
    {
        const auto Future = Self->Client->DescribeResources(
            MakeShared<Gs2::Deploy::Request::FDescribeResourcesRequest>()
                ->WithStackName(Self->StackName)
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

    TSharedPtr<FAsyncTask<FDescribeResourcesIteratorLoadTask>>
    FDescribeResourcesIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeResourcesIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeResourcesIterator::FDescribeResourcesIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Deploy::FGs2DeployRestClientPtr Client,
        const TOptional<FString> StackName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        StackName(StackName),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Deploy::Model::FResourcePtr& FDescribeResourcesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Deploy::Model::FResourcePtr FDescribeResourcesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeResourcesIterator::IteratorImpl& FDescribeResourcesIterator::IteratorImpl::operator++()
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

    FDescribeResourcesIterator::IteratorImpl FDescribeResourcesIterator::begin()
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
    FDescribeResourcesIterator::IteratorImpl FDescribeResourcesIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

