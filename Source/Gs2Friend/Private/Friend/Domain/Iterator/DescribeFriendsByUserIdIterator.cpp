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

#include "Friend/Domain/Iterator/DescribeFriendsByUserIdIterator.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/User.h"

namespace Gs2::Friend::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeFriendsByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FFriendUserPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeFriendsByUserId(
            MakeShared<Gs2::Friend::Request::FDescribeFriendsByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithUserId(Self->UserId)
                ->WithWithProfile(Self->WithProfile)
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

    TSharedPtr<FAsyncTask<FDescribeFriendsByUserIdIteratorLoadTask>>
    FDescribeFriendsByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeFriendsByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeFriendsByUserIdIterator::FDescribeFriendsByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Friend::FGs2FriendRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        WithProfile(WithProfile),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Friend::Model::FFriendUserPtr& FDescribeFriendsByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Friend::Model::FFriendUserPtr FDescribeFriendsByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeFriendsByUserIdIterator::IteratorImpl& FDescribeFriendsByUserIdIterator::IteratorImpl::operator++()
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

    FDescribeFriendsByUserIdIterator::IteratorImpl FDescribeFriendsByUserIdIterator::begin()
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
    FDescribeFriendsByUserIdIterator::IteratorImpl FDescribeFriendsByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

