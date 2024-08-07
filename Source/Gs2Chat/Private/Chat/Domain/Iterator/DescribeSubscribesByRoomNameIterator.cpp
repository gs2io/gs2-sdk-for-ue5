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

#include "Chat/Domain/Iterator/DescribeSubscribesByRoomNameIterator.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Chat::Domain::Iterator
{

    FDescribeSubscribesByRoomNameIterator::FDescribeSubscribesByRoomNameIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Chat::FGs2ChatRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RoomName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        RoomName(RoomName)
    {
    }

    FDescribeSubscribesByRoomNameIterator::FDescribeSubscribesByRoomNameIterator(
        const FDescribeSubscribesByRoomNameIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RoomName(From.RoomName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribesByRoomNameIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSubscribesByRoomNameIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSubscribesByRoomNameIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSubscribesByRoomNameIterator::FIterator& FDescribeSubscribesByRoomNameIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {

            const auto Future = Self->Client->DescribeSubscribesByRoomName(
                MakeShared<Gs2::Chat::Request::FDescribeSubscribesByRoomNameRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithRoomName(Self->RoomName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems();
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Chat::Model::FSubscribePtr& Item) { return Self->RoomName && Item->GetRoomName() != Self->RoomName; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSubscribesByRoomNameIterator::FIterator FDescribeSubscribesByRoomNameIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSubscribesByRoomNameIterator::FIterator FDescribeSubscribesByRoomNameIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSubscribesByRoomNameIterator::FIterator FDescribeSubscribesByRoomNameIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

