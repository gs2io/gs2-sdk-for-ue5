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

#include "Chat/Domain/Iterator/DescribeMessagesByUserIdIterator.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Room.h"

namespace Gs2::Chat::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeMessagesByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FMessagePtr>>> Result)
    {
        const auto ListParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
            Self->NamespaceName,
            TOptional<FString>("Singleton"),
            Self->RoomName,
            "Message"
        );
        if (Self->Cache->IsListCached<Gs2::Chat::Model::FMessage>(
            ListParentKey
        )) {
            Self->Result = Self->Cache->List<Gs2::Chat::Model::FMessage>(
                ListParentKey
            );
            Self->Last = true;
            return nullptr;
        }
        const auto Future = Self->Client->DescribeMessagesByUserId(
            MakeShared<Gs2::Chat::Request::FDescribeMessagesByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithRoomName(Self->RoomName)
                ->WithPassword(Self->Password)
                ->WithUserId(Self->UserId)
                ->WithStartAt(Self->StartAt)
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
                Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    Item->GetName()
                ),
                Item,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        if ((*Result)->Num() > 0) {
            Self->StartAt = *(**Result)[(*Result)->Num()-1]->GetCreatedAt() + 1;
        } else {
            Self->Last = true;
        }
        if (Self->Last) {
            Self->Cache->SetListCache<Gs2::Chat::Model::FMessage>(
                ListParentKey
            );
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeMessagesByUserIdIteratorLoadTask>>
    FDescribeMessagesByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeMessagesByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeMessagesByUserIdIterator::FDescribeMessagesByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Chat::FGs2ChatRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        RoomName(RoomName),
        Password(Password),
        UserId(UserId),
        StartAt(TOptional<int64>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Chat::Model::FMessagePtr& FDescribeMessagesByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Chat::Model::FMessagePtr FDescribeMessagesByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeMessagesByUserIdIterator::IteratorImpl& FDescribeMessagesByUserIdIterator::IteratorImpl::operator++()
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

    FDescribeMessagesByUserIdIterator::IteratorImpl FDescribeMessagesByUserIdIterator::begin()
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
    FDescribeMessagesByUserIdIterator::IteratorImpl FDescribeMessagesByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

