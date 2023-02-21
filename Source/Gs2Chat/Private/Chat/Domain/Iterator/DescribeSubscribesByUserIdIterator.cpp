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

#include "Chat/Domain/Iterator/DescribeSubscribesByUserIdIterator.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/User.h"

namespace Gs2::Chat::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribesByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FSubscribePtr>>> Result)
    {
        const auto ListParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId,
            "Subscribe"
        );
        if (Self->Cache->IsListCached<Gs2::Chat::Model::FSubscribe>(
            ListParentKey
        )) {
            Self->Result = Self->Cache->List<Gs2::Chat::Model::FSubscribe>(
                ListParentKey
            );
            Self->PageToken = TOptional<FString>();
            Self->Last = true;
            return nullptr;
        }
        const auto Future = Self->Client->DescribeSubscribesByUserId(
            MakeShared<Gs2::Chat::Request::FDescribeSubscribesByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
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
        for (auto Item : *R->GetItems())
        {
            Self->Cache->Put(
                ListParentKey,
                Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    Item->GetRoomName()
                ),
                Item,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        Self->PageToken = R->GetNextPageToken();
        Self->Last = !Self->PageToken.IsSet();
        if (Self->Last) {
            Self->Cache->SetListCache<Gs2::Chat::Model::FSubscribe>(
                ListParentKey
            );
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeSubscribesByUserIdIteratorLoadTask>>
    FDescribeSubscribesByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeSubscribesByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeSubscribesByUserIdIterator::FDescribeSubscribesByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Chat::FGs2ChatRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Chat::Model::FSubscribePtr& FDescribeSubscribesByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Chat::Model::FSubscribePtr FDescribeSubscribesByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeSubscribesByUserIdIterator::IteratorImpl& FDescribeSubscribesByUserIdIterator::IteratorImpl::operator++()
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

    FDescribeSubscribesByUserIdIterator::IteratorImpl FDescribeSubscribesByUserIdIterator::begin()
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
    FDescribeSubscribesByUserIdIterator::IteratorImpl FDescribeSubscribesByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

