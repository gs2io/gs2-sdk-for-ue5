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

#include "Dictionary/Domain/Iterator/DescribeEntriesIterator.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/User.h"

namespace Gs2::Dictionary::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeEntriesIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Dictionary::Model::FEntryPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeEntries(
            MakeShared<Gs2::Dictionary::Request::FDescribeEntriesRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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

    TSharedPtr<FAsyncTask<FDescribeEntriesIteratorLoadTask>>
    FDescribeEntriesIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeEntriesIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeEntriesIterator::FDescribeEntriesIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Dictionary::Model::FEntryPtr& FDescribeEntriesIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Dictionary::Model::FEntryPtr FDescribeEntriesIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeEntriesIterator::IteratorImpl& FDescribeEntriesIterator::IteratorImpl::operator++()
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

    FDescribeEntriesIterator::IteratorImpl FDescribeEntriesIterator::begin()
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
    FDescribeEntriesIterator::IteratorImpl FDescribeEntriesIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

