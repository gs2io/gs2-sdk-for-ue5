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
        UserId(UserId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeMessagesByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeMessagesByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeMessagesByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        StartAt(TOptional<int64>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeMessagesByUserIdIterator::FIterator& FDescribeMessagesByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>("Singleton"),
                Self->RoomName,
                "Message"
            );
            Range = Self->Cache->TryGetList<Gs2::Chat::Model::FMessage>(ListParentKey);
            if (Range) {
                RangeIteratorOpt = Range->CreateIterator();
                bLast = true;
                bEnd = !static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeMessagesByUserId(
                MakeShared<Gs2::Chat::Request::FDescribeMessagesByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithRoomName(Self->RoomName)
                    ->WithPassword(Self->Password)
                    ->WithUserId(Self->UserId)
                    ->WithStartAt(StartAt)
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
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ListParentKey,
                    Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            if (Range->Num() > 0) {
                StartAt = *(*Range)[Range->Num()-1]->GetCreatedAt() + 1;
            } else {
                bLast = true;
            }
            if (bLast) {
                Self->Cache->SetListCache(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeMessagesByUserIdIterator::FIterator FDescribeMessagesByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeMessagesByUserIdIterator::FIterator FDescribeMessagesByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeMessagesByUserIdIterator::FIterator FDescribeMessagesByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

